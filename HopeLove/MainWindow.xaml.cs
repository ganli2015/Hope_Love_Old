using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using GlobalInterface;
using DataWrapperCS;
using DataWrapper = GlobalInterface.DataWrapper;

namespace HopeLove
{
    /// <summary>
    /// MainWindow.xaml 的交互逻辑
    /// </summary>
    public partial class MainWindow : Window,UIForm
    {
        List<CPPManager> _managers = new List<CPPManager>();
        string _name = "HopeLove";

        public MainWindow()
        {
            InitializeComponent();

        }

        public void UpdateCommand(DataWrapper data)
        {
            foreach (CPPManager m in _managers)
            {
                m.Execute(data);
            }
        }

        public void Register(CPPManager manager)
        {
            manager.ConnectUI(this);
            _managers.Add(manager);
        }

        public void UpdateUI(DataWrapper data)
        {
            string str=data.GetData(DataType.OutputString) as string;
            if (str == null) return;

            TextBlock outputBox = CreateOutputBox(_name+"： "+str);
            stackPanel_Global.Children.Add(outputBox);

            TextBox inputBox = CreateInputBox();
            stackPanel_Global.Children.Add(inputBox);
            stackPanel_Global.Children[stackPanel_Global.Children.Count - 1].Focus();
        }

        private void Init()
        {
            TextBox inputBox = CreateInputBox();
            stackPanel_Global.Children.Add(inputBox);
            inputBox.Focus();

            ManageWrapper.Manager_HopeLove manager=new ManageWrapper.Manager_HopeLove();
            Register(manager);
        }

        private TextBox CreateInputBox()
        {
            TextBox inputBox = new TextBox();
            inputBox.Width = stackPanel_Global.Width*0.98;
            inputBox.KeyDown+=new KeyEventHandler(InputBoxEnterDown);

            return inputBox;
        }

        private TextBlock CreateOutputBox(string str)
        {
            TextBlock outputBox = new TextBlock();
            outputBox.Width = stackPanel_Global.Width * 0.98;
            outputBox.Text=str;

            return outputBox;
        }

        private void InputBoxEnterDown(object sender,KeyEventArgs e)
        {
            if(e.Key==Key.Enter)
            {
                TextBox box=sender as TextBox;
                if (box == null) return;

                box.IsReadOnly = true;
                box.Focusable = false;

                DataWrapper data = CreateDataWrapper(box.Text);
                UpdateCommand(data);

                e.Handled = true;               
            }

        }

        private GlobalInterface.DataWrapper CreateDataWrapper(string str)
        {
            DataWrapperCS.DataWrapper_CS data = new DataWrapperCS.DataWrapper_CS();
            data.SetData(DataType.InputString, str);

            return data;
        }

        private void Window_Initialized(object sender, EventArgs e)
        {
            Init();
        }


    }
}
