using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Shapes;

using System.IO;

namespace HopeLove
{
    /// <summary>
    /// A basic element in a chatting dialog,  including a sentence and the role saying this sentence and so on.
    /// </summary>
    class ChattingElement
    {
        public string Role { get; set; }
        public string Sentence { get; set; }
    }

    /// <summary>
    /// Chatting pair of Chatting element.
    /// It contains the chatting element and response of the element.
    /// </summary>
    class ChattingPair
    {
        public ChattingElement First { get; set; }
        public ChattingElement Second { get; set; }
    }

    /// <summary>
    /// ExtractChatting.xaml 的交互逻辑
    /// </summary>
    public partial class ExtractChatting : Window
    {
        /// <summary>
        /// File name of the chatting dialog.
        /// </summary>
        const string _filename = @"E:\Artificial Intelligence\Document\DataBase\莫莫.txt";
        const string HopeLoveMindPath = "..\\..\\..\\Mind\\HopeLoveData\\";

        /// <summary>
        /// Roles in the chatting.
        /// </summary>
        const string _role1 = "莫莫、";
        const string _role2 = "费曼的彩虹";


        public ExtractChatting()
        {
            InitializeComponent();

            List<ChattingPair> chattingPairs=Extract();
        }

        private List<ChattingPair> Extract()
        {
            if (!File.Exists(_filename)) return null;

            List<ChattingElement> elements = ExtractElement();
            //Output sentences in conversation.
            OutputConversation(elements);

            //Remove picture or expression in conversation.
            RemovePictureContent(elements);
            //Extract elements and their responses.
            List<ChattingPair> chattingPairs = ExtractChattingPairs(elements);

            return chattingPairs;
        }

        private void OutputConversation(List<ChattingElement> chattingElem)
        {
            StreamWriter sw = new StreamWriter(HopeLoveMindPath+"Conversation Sample.txt");
            foreach (ChattingElement elem in chattingElem)
            {
                sw.Write(elem.Sentence + "\r\n");
            }

            sw.Flush();
            sw.Close();
        }

        private List<ChattingElement> ExtractElement()
        {
            List<ChattingElement> res = new List<ChattingElement>();

            StreamReader sr = new StreamReader(_filename);
            while (!sr.EndOfStream)
            {
                string line = sr.ReadLine();
                if(line=="") continue;

                string role = ExtractRole(line);
                if(role=="") continue;

                //Only if the current line has a role, the next line is the sentence the role says.
                ChattingElement element = new ChattingElement();
                element.Role = role;
                element.Sentence = sr.ReadLine();

                res.Add(element);
            }

            return res;
        }

        private string ExtractRole(string line)
        {
            //Check whether the first term is a date.
            //If not , it is not the start of the element.
            string[] split = line.Split(' ');
            DateTime time;
            if(!DateTime.TryParse(split[0], out time))
            {
                return "";
            }

            if(split.Length!=3)
            {
                return "";
            }

            if(split[2]==_role1)
            {
                return _role1;
            }
            else if(split[2]==_role2)
            {
                return _role2;
            }
            else
            {
                return "";
            }
        }

        private void RemovePictureContent(List<ChattingElement> elements)
        {
            //Picture and expression contains brackets like "[表情]", "[图片]".
            const char leftBra = '[';
            const char rightBra = ']';
            for (int i=elements.Count-1;i >= 0;--i)
            {
                if (elements[i].Sentence.Contains(leftBra) && elements[i].Sentence.Contains(rightBra))
                {
                    elements.Remove(elements[i]);
                }
            }
        }

        private List<ChattingPair> ExtractChattingPairs(List<ChattingElement> elements)
        {
            List<ChattingPair> res = new List<ChattingPair>();

            for (int i=0;i<elements.Count-1;++i)
            {
                //If the current role is not the role of next element, then append a chatting pair.
                if(elements[i].Role!=elements[i+1].Role)
                {
                    ChattingPair pair=new ChattingPair();
                    pair.First = elements[i];
                    pair.Second = elements[i + 1];

                    res.Add(pair);
                }
            }

            return res;
        }
    }
}
