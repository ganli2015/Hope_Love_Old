﻿using System;
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
using System.Windows.Shapes;
using System.Xml;

namespace HopeLove
{
    /// <summary>
    /// AppendLogicStatementForm.xaml 的交互逻辑
    /// </summary>
    public partial class AppendLogicStatementForm : Window
    {
        const string ConditionCollectionNode = "ConditionCollection";
        const string ConditionNode = "Condition";
        const string ConstraintnNode = "Constraint";
        const string ResultNode = "Result";
        const string SymbolPairNode = "SymbolPair";
        const string FromNode = "From";
        const string ToNode = "To";
        const string SymbolNode = "Symbol";

        const string ArbSymbol = "Arb";
        const string EqualSymbol = "==";
        const string InequalSymbol = "!=";

        const string LogicStatementsFilename = "LogicStatements.txt";

        XmlDocument _document;
        List<TextBox> _conditionBox;
        List<TextBox> _constraintBox;
        List<TextBox> _resultBox;

        public AppendLogicStatementForm()
        {
            InitializeComponent();

            _document = new XmlDocument();
//             XmlElement root=_document.CreateElement("Root");
//             _document.AppendChild(root);
            _document.Load(CommonForAppendForm.HopeLoveMindPath + LogicStatementsFilename);

            CollectTextBoxes();
        }

        private void CollectTextBoxes()
        {
            _conditionBox = new List<TextBox>();
            _conditionBox.Add(textBox_Condition1);
            _conditionBox.Add(textBox_Condition2);
            _conditionBox.Add(textBox_Condition3);

            _constraintBox = new List<TextBox>();
            _constraintBox.Add(textBox_Constraint1);
            _constraintBox.Add(textBox_Constraint2);
            _constraintBox.Add(textBox_Constraint3);

            _resultBox = new List<TextBox>();
            _resultBox.Add(textBox_Result1);
            _resultBox.Add(textBox_Result2);
            _resultBox.Add(textBox_Result3);
        }

        private void button_Append_Click(object sender, RoutedEventArgs e)
        {
            XmlElement statementNode = _document.CreateElement("LogicStatement");

            XmlElement conditionsNode = _document.CreateElement(ConditionCollectionNode);
            conditionsNode.SetAttribute("Relation", "And");
            _conditionBox.ForEach(b=>
            {
                if (b.Text != "")
                {
                    WriteConditionToFile(b.Text, conditionsNode, _document);
                }
            });
            statementNode.AppendChild(conditionsNode);

            _constraintBox.ForEach(b =>
            {
                if (b.Text != "")
                {
                    WriteContraintToFile(b.Text, statementNode);
                }
            });

            _resultBox.ForEach(b =>
            {
                if (b.Text != "")
                {
                    WriteResultToFile(b.Text, statementNode, _document);
                }
            });

            XmlNode root = _document.SelectSingleNode("Root");
            root.AppendChild(statementNode);

            _document.Save(CommonForAppendForm.HopeLoveMindPath + LogicStatementsFilename);
        }

        private void WriteConditionToFile(string str, XmlNode node, XmlDocument document)
        {
            XmlElement conditionNode = document.CreateElement(ConditionNode);

            WriteSymbolPairsToFile(str, conditionNode, document);

            node.AppendChild(conditionNode);
        }

        private void WriteResultToFile(string str, XmlNode node, XmlDocument document)
        {
            XmlElement resultNode = document.CreateElement(ResultNode);

            WriteSymbolPairsToFile(str, resultNode, document);

            node.AppendChild(resultNode);
        }

        private void WriteSymbolPairsToFile(string str, XmlNode node, XmlDocument document)
        {
            string[] pairs = str.Split(',');
            foreach (string pair in pairs)
            {
                List<string> fromTo = SplitAndRemoveBlank(pair,"->");
                if (fromTo.Count != 2)
                {
                    throw new ArgumentOutOfRangeException("fromTo.Length != 2");
                }

                //Write from symbol
                XmlElement fromNode = document.CreateElement(FromNode);
                if (fromTo[0].Contains(ArbSymbol))//if it is Arbitrariness
                {
                    fromNode.InnerText = fromTo[0];
                }
                else//if it is a common symbol
                {
                    Word_ID from = CommonForAppendForm.StringToWordID(fromTo[0]);
                    fromNode.SetAttribute("ID", Convert.ToString(from.id));
                    fromNode.SetAttribute("Word", from.word);
                }

                //Write to symbol
                XmlElement toNode = document.CreateElement(ToNode);
                if (fromTo[1].Contains(ArbSymbol))//if it is Arbitrariness
                {
                    toNode.InnerText = fromTo[1];
                }
                else//if it is a common symbol
                {
                    Word_ID to = CommonForAppendForm.StringToWordID(fromTo[1]);
                    toNode.SetAttribute("ID", Convert.ToString(to.id));
                    toNode.SetAttribute("Word", to.word);
                }

                XmlElement symbolPairNode = document.CreateElement(SymbolPairNode);           
                symbolPairNode.AppendChild(fromNode);
                symbolPairNode.AppendChild(toNode);

                node.AppendChild(symbolPairNode);
            }
        }


        private void WriteContraintToFile(string str, XmlNode node)
        {
            if (str.Contains(EqualSymbol))
            {
                List<string> symbolSplit = SplitAndRemoveBlank(str,EqualSymbol);
                if (symbolSplit.Count == 2)
                {
                    XmlElement constrElem = _document.CreateElement("Equality");
                    constrElem.AppendChild(CreateSimpleElement(SymbolNode, symbolSplit[0]));
                    constrElem.AppendChild(CreateSimpleElement(SymbolNode, symbolSplit[1]));
                    node.AppendChild(constrElem);
                }
            }
            else if(str.Contains(InequalSymbol))
            {
                List<string> symbolSplit = SplitAndRemoveBlank(str, InequalSymbol);
                if (symbolSplit.Count == 2)
                {
                    XmlElement constrElem = _document.CreateElement("Inequality");
                    constrElem.AppendChild(CreateSimpleElement(SymbolNode, symbolSplit[0]));
                    constrElem.AppendChild(CreateSimpleElement(SymbolNode, symbolSplit[1]));
                    node.AppendChild(constrElem);
                }
            }
        }

        private XmlElement CreateSimpleElement(string tagName, string text)
        {
            XmlElement elem = _document.CreateElement(tagName);
            elem.InnerText = text;

            return elem;
        }

        private List<string> SplitAndRemoveBlank(string str,string tag)
        {
            return CommonForAppendForm.RemoveBlank(str.Split(tag.ToCharArray()));
        }
    }
}
