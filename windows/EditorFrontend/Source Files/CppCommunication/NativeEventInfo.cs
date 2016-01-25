using System;
using System.Collections.Generic;
using System.Linq;
using System.Reflection;
using System.Text;
using System.Threading.Tasks;

namespace Editor.Source_Files.CppCommunication
{

	//Native event information
    public class NativeEventInfo
    {
        public object target;
        public MethodInfo methodInfo;
    }
}
