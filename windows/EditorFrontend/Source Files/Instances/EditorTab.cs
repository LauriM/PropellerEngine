using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;

namespace Editor.Source_Files.Objects
{
    public class EditorTab
    {
        public EditorView view;
        public EditorInstance instance;
        public IntPtr handle;

        public bool initDone;

        public EditorTab(EditorView v, EditorInstance i, IntPtr h)
        {
            view = v;
            instance = i;
			handle = h;

            initDone = false;
        }

		public void initInstance()
        {
            instance.initializeRenderer(handle);
			instance.initialize();

            initDone = true;
        }
	}
}
