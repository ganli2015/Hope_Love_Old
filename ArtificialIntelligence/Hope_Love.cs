using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using Interactor;
using DataWrapperCS;

namespace ArtificialIntelligenceUI
{
    public partial class Hope_Love : ParentFormofAI,ArtificialIntelligences
    {
        private string _inputdata;
        private Observable _observable;
        public Hope_Love(DataWrapper datawrapper,Observable interactor)
        {
            InitializeComponent();
            _observable = interactor;
            _observable.RegisterObserver(this);
            _datawrapper = datawrapper;
            _datawrapper.Observable = _observable;
            this.Show();
        }

        public string GetData()
        {return _inputdata;}
        public void SetData(string data)
        {
            _inputdata = data;
        }
        public void UpdateUI()
        {
            textBox_Output.Text = _datawrapper.outputsentence;
            return;
        }

        private void button_send_Click(object sender, EventArgs e)
        {
            _datawrapper.inputsentence = Convert.ToString(textBox_Input.Text);
            _observable.UpdateCommand();
        }
    }
}
