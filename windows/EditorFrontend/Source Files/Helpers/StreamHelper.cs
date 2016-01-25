using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Editor.Source_Files.Helpers
{

	//Contains useful functions to manage a stream from/to the engine
    public class StreamHelper
    {
        private static byte[] GetBytes(string str)
		{
			byte[] bytes = new byte[str.Length * sizeof(char)];
			System.Buffer.BlockCopy(str.ToCharArray(), 0, bytes, 0, bytes.Length);
			return bytes;
		}

        public static void WriteString(BinaryWriter writer, String str)
        {
            uint len = (uint)str.Length;

            writer.Write(len);
            writer.Write(str.ToCharArray());
        }

		public static String ReadString(BinaryReader reader)
        {
            int len = reader.ReadInt32();
			char[] buffer = new char[len];
			buffer = reader.ReadChars(len);
			return new String(buffer);
		}

		//Used to read by specific type
		public static void ReadToObject(BinaryReader reader, ref Object obj)
        {
			Type t = obj.GetType();

			if(t == typeof(String))
            {
                obj = ReadString(reader);
                return;
            }

			if(t == typeof(int))
            {
				obj = reader.ReadInt32();
				return;
            }

			if (t == typeof(UInt32))
			{
				obj = reader.ReadUInt32();
				return;
			}

			if(t == typeof(double))
			{
				obj = reader.ReadDouble();
				return;
			}

			if(t == typeof(IntPtr))
			{
				obj = (IntPtr)reader.ReadInt32(); //32Bit hack, doesn't work on 64platform
				return;
			}

            Console.WriteLine(" !!!!!!!!!!!!!!!!!!!!!!!!!!!!                     Invalid parameters for c# events! Perhaps add one to the list above or change type.");
            Debugger.Break();
        }

		/*
		public static void ReadPropertyType(BinaryReader reader)
        {
			switch(prop.propertyType)
            {
                case PropertyType.Unsigned:
                    prop.setValue(reader.ReadUInt32());
                    break;
				case PropertyType.Int:
                    prop.setValue(reader.ReadInt32());
                    break;
                case PropertyType.String:
                    prop.setValue(ReadString(reader));
                    break;
                case PropertyType.Vec2:
					prop.setValueVec2("Vector value not processed");
                    break;
			}
		}
		*/
    }
}
