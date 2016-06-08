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
        const string EqualityNode = "Equality";
        const string InequalityNode = "Inequality";

        //Special symbol
        const string ArbSymbol = "Arb";
        const string NumSymbol = "Num";
        const string VerbSymbol = "Verb";
        List<string> _specialSymbols;

        const string EqualSymbol = "==";
        const string InequalSymbol = "!=";

        const string LogicStatementsFilename = "LogicStatements.xml";

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

            _specialSymbols = new List<string>();
            _specialSymbols.Add(ArbSymbol);
            _specialSymbols.Add(NumSymbol);
            _specialSymbols.Add(VerbSymbol);
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
                XmlElement fromNode = CreateFromToNode(fromTo[0],FromNode);

                //Write to symbol
                XmlElement toNode = CreateFromToNode(fromTo[1],ToNode);

                XmlElement symbolPairNode = document.CreateElement(SymbolPairNode);           
                symbolPairNode.AppendChild(fromNode);
                symbolPairNode.AppendChild(toNode);

                node.AppendChild(symbolPairNode);
            }
        }

        private XmlElement CreateFromToNode(string fromTo,string nodeTag)
        {
            XmlElement fromNode = _document.CreateElement(nodeTag);
            if (ContainSpecialSymbol(fromTo))//if it is Arbitrariness
            {
                fromNode.InnerText = fromTo;
            }
            else//if it is a common symbol
            {
                Word_ID from = CommonForAppendForm.StringToWordID(fromTo);
                fromNode.SetAttribute("ID", Convert.ToString(from.id));
                fromNode.SetAttribute("Word", from.word);
            }

            return fromNode;
        }

        private bool ContainSpecialSymbol(string str)
        {
            foreach (string sp in _specialSymbols)
            {
                if (str.Contains(sp))
                {
                    return true;
                }
            }

            return false;
        }

        private void WriteContraintToFile(string str, XmlNode node)
        {
            if (str.Contains(EqualSymbol))
            {
                List<string> symbolSplit = SplitAndRemoveBlank(str,EqualSymbol);
                if (symbolSplit.Count == 2)
                {
                    XmlElement constrElem = _document.CreateElement(EqualityNode);
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
                    XmlElement constrElem = _document.CreateElement(InequalityNode);
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
