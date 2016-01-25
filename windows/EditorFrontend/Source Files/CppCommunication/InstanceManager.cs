using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace Editor.Source_Files
{
    public static unsafe class InstanceManager
    {
		[DllImport("EditorBackend.dll")]
		private static extern IntPtr createInstance(String buffer);
		 
		[DllImport("EditorBackend.dll")]
		private static extern void releaseInstance(IntPtr ptr);

        [DllImport("EditorBackend.dll")]
        private static extern void syncInstance(IntPtr ptr, IntPtr inBuffer, [In, Out] IntPtr *outBuffer);

        [DllImport("EditorBackend.dll")]
		private static extern void finalizeSync(IntPtr ptr);


		public static IntPtr create(String name)
        {
			return createInstance(name);
		}

		public static void release(IntPtr ptr)
        {
			releaseInstance(ptr);
		}

		public static void sync(IntPtr ptr, IntPtr inBuffer, [In,Out] IntPtr *outBuffer)
        {
			syncInstance(ptr, inBuffer, outBuffer);
        }

        internal static void finalize(IntPtr instancePtr)
        {
			finalizeSync(instancePtr);
        }
    }
}
