using System;
using System.Collections.Generic;
using System.Configuration;
using System.Data;
using System.Linq;
using System.Windows;

namespace HopeLove
{

    /// <summary>
    /// App.xaml 的交互逻辑
    /// </summary>
    public partial class App : Application
    {
        enum FormType
        {
            Main,
            AppendConcept,
            AppendLogicStatement
        }

        FormType formType;

        public App()
        {
            formType = FormType.Main;
        }

        private void Application_Startup(object sender, StartupEventArgs e)
        {
            Window myApp = null;
            switch (formType)
            {
                case FormType.Main:
                    {
                        myApp = new MainWindow();
                        break;
                    }
                case FormType.AppendConcept:
                    {
                        myApp = new AppendConceptForm();
                        break;
                    }
                case FormType.AppendLogicStatement:
                    {
                        myApp = new AppendLogicStatementForm();
                        break;
                    }
                default:
                    {
                        throw new ApplicationException();
                    }
            }
            
            myApp.ShowDialog();
            Shutdown();
        }
    }
}
