using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using ArtificialIntelligenceUI;
using Interactor;
using DataWrapperCS;
using ManageWrapper;
using System.Runtime.InteropServices;

namespace StartForm
{
    public partial class MainForm : Form
    {
        DataWrapper _datawrapper;
        public MainForm()
        {
            InitializeComponent();
            _datawrapper = new DataWrapper();
            Observable observable = new InteractorHL();
            _datawrapper.Observable = observable;
        }

        private void Button_Hope_Love_Click(object sender, EventArgs e)
        {
            Observable observable = _datawrapper.Observable;
            ParentFormofAI HLform = new Hope_Love(_datawrapper,observable);
            HLform.Location = this.Location;
            HLform.Visible = false;
            HLform.Text = "Hope&Love";
            HLform.ShowDialog();
            
        }
    }
}
