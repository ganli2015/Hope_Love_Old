using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Microsoft.VisualBasic.ApplicationServices;
using ArtificialIntelligenceUI;
using ManageWrapper;
using Interactor;

namespace StartForm
{
    class Program
    {
        static void Main(string[] args)
        {
            /*MainForm aform = new MainForm();*/
            MyApplication application = new MyApplication();
            application.Run(args);
        }
    }
    public class MyApplication : WindowsFormsApplicationBase
    {
        String[] _args;

        public String[] Args
        {
            get { return _args; }
            set { _args = value; }
        }
        protected override void OnCreateMainForm()
        {
            this.MainForm = new MainForm();
        }

    };
}
