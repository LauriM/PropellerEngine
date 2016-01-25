using Editor.Source_Files.CppCommunication;
using Editor.Source_Files.Helpers;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Reflection;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace Editor.Source_Files
{

    public abstract class NativeInstance
    {
        IntPtr instancePtr;

		private bool requestShutdown; // Set true when the updater thread should kill the instance.

        protected UnmanagedMemoryStream stream;
        protected IntPtr bufferPointer;
        protected BinaryWriter binaryWriter;

		protected UInt32 callCount = 0;

        private UInt32 maxCallLenght = 15000;

        public Dictionary<String, NativeEventInfo> methodList;

		public IntPtr getInstancePtr() { return instancePtr; }

		public NativeInstance(String intanceName)
        {
			requestShutdown = false;
            instancePtr = InstanceManager.create(intanceName);
            bufferPointer = Marshal.AllocHGlobal((int)maxCallLenght); //TODO: doesn't handle situations where the buffer is longer than maxCallLenght!

            methodList = new Dictionary<String, NativeEventInfo>();

            resetBuffers();
        }

		public bool getShutdownState() { return requestShutdown; }

		public void instanceShutdown() { requestShutdown = true; }

		public virtual void update() {}

		~NativeInstance()
		{
			lock (this)
			{
				flush();

				InstanceManager.release(instancePtr);

				Marshal.FreeHGlobal(bufferPointer);

				Console.WriteLine("[C#] NativeInstance released!");
			}
		}

		public void registerEvent(String eventName, object obj, MethodInfo methodInfo)
        {
			lock (this)
			{
				NativeEventInfo nei = new NativeEventInfo();
				nei.target = obj;
				nei.methodInfo = methodInfo;

				methodList.Add(eventName, nei);
			}
		}

		//Write a command into the stream
		//Calls Native functions!
		protected unsafe void call(String command, params object[] args)            
        {
            lock (this)
            {
				++callCount;

                binaryWriter.Write((int)StreamInstructionTypes.STREAM_INSTRUCTION_CALL);

                StreamHelper.WriteString(binaryWriter, command);

                foreach (object arg in args)
                {
					if(arg.GetType() == typeof(String))
                    {
						StreamHelper.WriteString(binaryWriter, (dynamic)arg);
						continue;
                    }

					if(arg.GetType() == typeof(IntPtr))
                    {
						IntPtr ip = (dynamic)arg;
                        binaryWriter.Write(ip.ToInt64());
                        continue;
                    }

                    binaryWriter.Write((dynamic)arg);
                }
            }
        }

		private unsafe void resetBuffers()
        {
            stream = new UnmanagedMemoryStream((byte*)bufferPointer, maxCallLenght, maxCallLenght, FileAccess.Write);
            binaryWriter = new BinaryWriter(stream);

            InstanceManager.finalize(instancePtr);
			callCount = 0;
        }

		public void flush()
        {
			lock (this)
			{
				if (callCount == 0)
					return;

				//Insert the EOF
				binaryWriter.Write((int)StreamInstructionTypes.STREAM_INSTRUCTION_EOF);

                IntPtr incomingPointer;

                unsafe
                {
					InstanceManager.sync(instancePtr, bufferPointer, &incomingPointer);

                    UnmanagedMemoryStream strm = new UnmanagedMemoryStream((byte*)incomingPointer, maxCallLenght, maxCallLenght, FileAccess.Read);

                    BinaryReader reader = new BinaryReader(strm);

                    UInt32 instruction;
					bool EOF = false;
					while (!EOF)
					{
						try
						{
							instruction = reader.ReadUInt32();
						}
						catch(Exception eek)
						{
							Console.WriteLine("EOF is invalid!");
							Console.WriteLine(eek.ToString());
							break;
						}
						
						switch(instruction)
						{
							case (int)StreamInstructionTypes.STREAM_INSTRUCTION_CALL:
								String cmd = StreamHelper.ReadString(reader);
								handleEvent(cmd, reader);
								break;
							case (int)StreamInstructionTypes.STREAM_INSTRUCTION_EOF:
								EOF = true;
								break;
						}
					}

					resetBuffers();
                }
			}
        }

		//Handle incoming native event
        private void handleEvent(String cmd, BinaryReader reader)
        {
			if (cmd == "")
			{
				Console.WriteLine("Empty event received!");
				return;
			}

			//if the engine crashes around here, the commandlist may have grown too big, and the commandbuffer is too small (?)

			NativeEventInfo nativeEventInfo = methodList.First(t => t.Key == cmd).Value;
			MethodInfo info = nativeEventInfo.methodInfo;

			if(info == null)
			{
				Console.WriteLine("[C# NativeInstance] REQUESTED EVENT NOT IMPLEMENTED OR PRIVATE!");
				return;
			}

            ParameterInfo[] parameters = info.GetParameters();

            List<object> callParameters = new List<object>();

			foreach(ParameterInfo p in parameters)
            {
                Type t = p.ParameterType;

                object obj;

				if(t == typeof(String))
                {
                    string str = "";
                    obj = str;
                }
				else
                {
                    obj = Activator.CreateInstance(t, null);
                }

                StreamHelper.ReadToObject(reader, ref obj);

                callParameters.Add(obj);
            }

            info.Invoke(nativeEventInfo.target, callParameters.ToArray());
        }
    }
}
