﻿#pragma checksum "..\..\..\CommonWordTable.xaml" "{406ea660-64cf-4c82-b6f0-42d48172a799}" "FDAF52AC3A1F8CBA6FB00218EA574B32"
//------------------------------------------------------------------------------
// <auto-generated>
//     此代码由工具生成。
//     运行时版本:4.0.30319.42000
//
//     对此文件的更改可能会导致不正确的行为，并且如果
//     重新生成代码，这些更改将会丢失。
// </auto-generated>
//------------------------------------------------------------------------------

using System;
using System.Diagnostics;
using System.Windows;
using System.Windows.Automation;
using System.Windows.Controls;
using System.Windows.Controls.Primitives;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Ink;
using System.Windows.Input;
using System.Windows.Markup;
using System.Windows.Media;
using System.Windows.Media.Animation;
using System.Windows.Media.Effects;
using System.Windows.Media.Imaging;
using System.Windows.Media.Media3D;
using System.Windows.Media.TextFormatting;
using System.Windows.Navigation;
using System.Windows.Shapes;
using System.Windows.Shell;


namespace HopeLove {
    
    
    /// <summary>
    /// CommonWordTable
    /// </summary>
    public partial class CommonWordTable : System.Windows.Window, System.Windows.Markup.IComponentConnector {
        
        
        #line 15 "..\..\..\CommonWordTable.xaml"
        [System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1823:AvoidUnusedPrivateFields")]
        internal System.Windows.Controls.ListBox listBox_CommonWord;
        
        #line default
        #line hidden
        
        
        #line 16 "..\..\..\CommonWordTable.xaml"
        [System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1823:AvoidUnusedPrivateFields")]
        internal System.Windows.Controls.TextBlock textBlock_Meaning;
        
        #line default
        #line hidden
        
        
        #line 17 "..\..\..\CommonWordTable.xaml"
        [System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1823:AvoidUnusedPrivateFields")]
        internal System.Windows.Controls.TextBox textBox_Search;
        
        #line default
        #line hidden
        
        
        #line 18 "..\..\..\CommonWordTable.xaml"
        [System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1823:AvoidUnusedPrivateFields")]
        internal System.Windows.Controls.Button button_Search;
        
        #line default
        #line hidden
        
        
        #line 19 "..\..\..\CommonWordTable.xaml"
        [System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1823:AvoidUnusedPrivateFields")]
        internal System.Windows.Controls.ListBox listBox_Search;
        
        #line default
        #line hidden
        
        private bool _contentLoaded;
        
        /// <summary>
        /// InitializeComponent
        /// </summary>
        [System.Diagnostics.DebuggerNonUserCodeAttribute()]
        [System.CodeDom.Compiler.GeneratedCodeAttribute("PresentationBuildTasks", "4.0.0.0")]
        public void InitializeComponent() {
            if (_contentLoaded) {
                return;
            }
            _contentLoaded = true;
            System.Uri resourceLocater = new System.Uri("/HopeLove;component/commonwordtable.xaml", System.UriKind.Relative);
            
            #line 1 "..\..\..\CommonWordTable.xaml"
            System.Windows.Application.LoadComponent(this, resourceLocater);
            
            #line default
            #line hidden
        }
        
        [System.Diagnostics.DebuggerNonUserCodeAttribute()]
        [System.CodeDom.Compiler.GeneratedCodeAttribute("PresentationBuildTasks", "4.0.0.0")]
        [System.ComponentModel.EditorBrowsableAttribute(System.ComponentModel.EditorBrowsableState.Never)]
        [System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Design", "CA1033:InterfaceMethodsShouldBeCallableByChildTypes")]
        [System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Maintainability", "CA1502:AvoidExcessiveComplexity")]
        [System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1800:DoNotCastUnnecessarily")]
        void System.Windows.Markup.IComponentConnector.Connect(int connectionId, object target) {
            switch (connectionId)
            {
            case 1:
            this.listBox_CommonWord = ((System.Windows.Controls.ListBox)(target));
            
            #line 15 "..\..\..\CommonWordTable.xaml"
            this.listBox_CommonWord.SelectionChanged += new System.Windows.Controls.SelectionChangedEventHandler(this.listBox_CommonWord_SelectionChanged);
            
            #line default
            #line hidden
            
            #line 15 "..\..\..\CommonWordTable.xaml"
            this.listBox_CommonWord.GotFocus += new System.Windows.RoutedEventHandler(this.listBox_CommonWord_GotFocus);
            
            #line default
            #line hidden
            return;
            case 2:
            this.textBlock_Meaning = ((System.Windows.Controls.TextBlock)(target));
            return;
            case 3:
            this.textBox_Search = ((System.Windows.Controls.TextBox)(target));
            
            #line 17 "..\..\..\CommonWordTable.xaml"
            this.textBox_Search.KeyDown += new System.Windows.Input.KeyEventHandler(this.textBox_Search_KeyDown);
            
            #line default
            #line hidden
            return;
            case 4:
            this.button_Search = ((System.Windows.Controls.Button)(target));
            
            #line 18 "..\..\..\CommonWordTable.xaml"
            this.button_Search.Click += new System.Windows.RoutedEventHandler(this.button_Search_Click);
            
            #line default
            #line hidden
            return;
            case 5:
            this.listBox_Search = ((System.Windows.Controls.ListBox)(target));
            
            #line 19 "..\..\..\CommonWordTable.xaml"
            this.listBox_Search.SelectionChanged += new System.Windows.Controls.SelectionChangedEventHandler(this.listBox_Search_SelectionChanged);
            
            #line default
            #line hidden
            
            #line 19 "..\..\..\CommonWordTable.xaml"
            this.listBox_Search.GotFocus += new System.Windows.RoutedEventHandler(this.listBox_Search_GotFocus);
            
            #line default
            #line hidden
            return;
            }
            this._contentLoaded = true;
        }
    }
}

