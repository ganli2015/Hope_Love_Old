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
using System.IO;

namespace HopeLove
{
    

    /// <summary>
    /// AppendConceptForm.xaml 的交互逻辑
    /// </summary>
    public partial class AppendConceptForm : Window
    {
        List<Word_ID> _nonBaseConcepts = new List<Word_ID>();
        List<Word_ID> _baseConcepts = new List<Word_ID>();
        List<Connection_Info> _connectionInfos = new List<Connection_Info>();
        CommonWordTable _commonWordTable;

        const string NonBaseConceptString_InitialFilename = "NonBaseConceptString_Initial.txt";
        const string ConceptConnections_InitialFilename = "ConceptConnections_Initial.txt";
        const string BaseConceptsStringFilename = "BaseConceptsString.txt";
        const string HopeLoveMindPath = "HopeLoveData\\";

        Encoding MyEncoding = null;

        public AppendConceptForm()
        {
            InitializeComponent();

            MyEncoding = Encoding.Default;

            Init();
        }

        private void Init()
        {
            _baseConcepts = InputWordFromFile(HopeLoveMindPath + BaseConceptsStringFilename);
            _nonBaseConcepts = InputWordFromFile(HopeLoveMindPath + NonBaseConceptString_InitialFilename);
            _connectionInfos = InputConnectionFromFile(HopeLoveMindPath + ConceptConnections_InitialFilename);

//             StreamWriter sw = new StreamWriter(HopeLoveMindPath + "1.txt",false,MyEncoding);
//             _nonBaseConcepts.ForEach(w_i =>
//             {
//                 Connection_Info con = SearchConnectionInfo(w_i);
//                 if (con != null)
//                 {
//                     sw.Write(w_i.ToString() + "\r\n");
//                 }
//             });
//             sw.Flush();
        }

        private List<Word_ID> InputWordFromFile(string filename)
        {
            List<Word_ID> res = new List<Word_ID>();
            StreamReader sr = new StreamReader(filename,MyEncoding);
            while (!sr.EndOfStream)
            {
                string line = sr.ReadLine();
                string[] split = line.Split(' ');
                if (split.Length != 3)
                {
                    throw new ArgumentOutOfRangeException();
                }

                Word_ID w_i=new Word_ID();
                w_i.id = Convert.ToInt32(split[0]);
                w_i.word = split[1];
                w_i.pos = (PartOfSpeech)Convert.ToInt32(split[2]);

                res.Add(w_i);
            }

            return res;
        }

        private Word_ID TransformToIdentity(string id ,string word)
        {
            Word_ID res = new Word_ID();
            res.word = word;
            res.id = Convert.ToInt32(id);
            SearchWordPos(res);

            return res;
        }

        private void SearchWordPos(Word_ID w_i)
        {
            Word_ID exist1 = _baseConcepts.Find(wi => w_i.word == wi.word && w_i.id == wi.id);
            Word_ID exist2 = _nonBaseConcepts.Find(wi => w_i.word == wi.word && w_i.id == wi.id);

            if (exist1 != null)
            {
                w_i.pos = exist1.pos;
            }
            else if (exist2 != null)
            {
                w_i.pos = exist2.pos;
            }
        }

        private List<Connection_Info> InputConnectionFromFile(string filename)
        {
            List<Connection_Info> res = new List<Connection_Info>();
            StreamReader sr = new StreamReader(filename, MyEncoding);
            while (!sr.EndOfStream)
            {
                string line = sr.ReadLine();
                string[] splitArray=line.Split(' ');
                List<string> split=new List<string>();
                for (int i=0;i<splitArray.Length;++i)
                {
                    split.Add(splitArray[i]);
                }

				if(split.Count<2)
				{
					throw new ArgumentOutOfRangeException("Error in InputConnectionFromFile");
				}

				Connection_Info connnection_info=new Connection_Info();
				//读取当前的word和id
				connnection_info.me=TransformToIdentity(split[0],split[1]);

				if(split.Count==2)//没有ConceptEdge就继续下个循环
				{
					res.Add(connnection_info);
					continue;
				}

				//读取Edge
				int index=2;//开始遍历后面的string
				while(true)
				{
					if(split[index]!="to")
					{
						throw new ArgumentOutOfRangeException("Error in InputConnectionFromFile");
					}
					else
					{
						index++;
					}

					//读取依赖的word及其id
					Edge_Info edge_info=new Edge_Info();
					edge_info.to=TransformToIdentity(split[index],split[index+1]);
					index+=2;

					//读取修饰词
					int nextTo=split.FindIndex(index,s=>s=="to");
                    if (nextTo == -1)
                    {
                        nextTo = split.Count;
                    }

					if((nextTo-index)%2!=0)//string的个数必须是偶数，因为word和id总是成对出现
					{
						throw new ArgumentOutOfRangeException("Error in InputConnectionFromFile");
					}
					List<Word_ID> modifications=new List<Word_ID>();
                    for (int i = index; i != nextTo;i+=2 )
                    {
                        modifications.Add(TransformToIdentity(split[i], split[i+1]));
                    }
					edge_info.mods=modifications;

					connnection_info.edge_infos.Add(edge_info);

                    if (nextTo == split.Count)
					{
						break;
					}

					index=nextTo;//移动index到下一个to的位置。
				}

				res.Add(connnection_info);
            }

            return res;
        }

        private void textBox_NewConcept_TextChanged(object sender, TextChangedEventArgs e)
        {
            Word_ID w_i = new Word_ID();
            w_i.word = textBox_NewConcept.Text;
            w_i.id = GetTextBoxId(textBox_NewID);
            if (w_i.id == -1)
            {
                return;
            }

            Word_ID exist1 = _baseConcepts.Find(wi => wi.WeakSame(w_i));
            Word_ID exist2 = _nonBaseConcepts.Find(wi => wi.WeakSame(w_i));
            if (exist1!=null || exist2!=null)
            {
                string message="Exist";
                Connection_Info con_info=SearchConnectionInfo(w_i);
                if(con_info!=null)//输入连接信息
                {
                    message+=": "+con_info.ToString();
                }
                if (exist1 != null)
                {
                    message += ": Base.";
                }
                textBlock_NewConceptInfo.Text = message;
            }
            else
            {
                textBlock_NewConceptInfo.Text = "Not Exist";
            }
        }

        private int GetTextBoxId(TextBox block)
        {
            int res ;
            if (!int.TryParse(block.Text, out res))
            {
                return -1;
            }
            return res;
        }

        private PartOfSpeech GetTextBoxPOS(TextBox block)
        {
            int res;
            if (!int.TryParse(block.Text, out res))
            {
                return PartOfSpeech.Unknown;
            }
            return (PartOfSpeech)res;
        }

        private bool WordInList(Word_ID w_i, List<Word_ID> wiList)
        {
            Word_ID exist1 = wiList.Find(wi => wi.WeakSame(w_i));
            if (exist1 == null)
            {
                return false;
            }
            else
            {
                return true;
            }
        }

        private int MaxID(string str, List<Word_ID> wiList)
        {
            int res = -1;
            foreach (Word_ID wi in wiList)
            {
                if (wi.word == str)
                {
                    if (wi.id > res)
                    {
                        res = wi.id;
                    }
                }
            }

            return res;
        }

        private void button_Append_Click(object sender, RoutedEventArgs e)
        {
            Word_ID newWord = GetNewConcept();
            Word_ID toWord = GetToConcept();
            List<Word_ID> mods = GetConnectionConcepts();

            try
            {
                CheckWordNoEmpty(newWord);
                if (checkBox_IsBase.IsChecked==false)
                {
                    CheckWordNoEmptyWeak(toWord);
                }
                else
                {
                    CheckHasNoConnections(newWord);
                }
                CheckWordExisted(newWord);
                CheckWordID(newWord);
                CheckPOSUnique(newWord);
                CheckPos_Me_To(newWord, toWord);
            }
            catch (System.Exception ex)
            {
                MessageBox.Show(ex.Message);
                return;
            }

            if (checkBox_IsBase.IsChecked==true)
            {
                WriteBaseFile(newWord);
            }
            else
            {
                WriteNonBaseFile(newWord);
                WriteConnnectionFile(newWord, toWord, mods);
            }

            Init();
        }

        private Word_ID GetNewConcept()
        {
            Word_ID newWord = new Word_ID();
            newWord.word = textBox_NewConcept.Text;
            newWord.id = GetTextBoxId(textBox_NewID);
            newWord.pos = GetTextBoxPOS(textBox_POS);

            return newWord;
        }

        private Word_ID GetToConcept()
        {
            Word_ID newWord = new Word_ID();
            newWord.word = textBox_toConcept.Text;
            newWord.id = GetTextBoxId(textBox_toConceptID);

            return newWord;
        }

        private List<Word_ID> GetConnectionConcepts()
        {
            Word_ID edgeWord1 = new Word_ID();
            edgeWord1.word = textBox_Mod1.Text;
            edgeWord1.id = GetTextBoxId(textBox_Mod1ID);

            Word_ID edgeWord2 = new Word_ID();
            edgeWord2.word = textBox_Mod2.Text;
            edgeWord2.id = GetTextBoxId(textBox_Mod2ID);

            List<Word_ID> res = new List<Word_ID>();
            if(edgeWord1.id>=0)
                res.Add(edgeWord1);
            if (edgeWord2.id >= 0)
                res.Add(edgeWord2);

            return res;
        }

        private void CheckWordNoEmpty(Word_ID w_i)
        {
            if (w_i.id == -1 || w_i.pos == PartOfSpeech.Unknown || w_i.word=="")
            {
                throw new ApplicationException("Invalid Word");
            }
        }

        private void CheckWordNoEmptyWeak(Word_ID w_i)
        {
            if (w_i.id == -1 || w_i.word == "")
            {
                throw new ApplicationException("Invalid Word");
            }
        }

        private void WriteNonBaseFile(Word_ID newWord)
        {
            StreamWriter sw = new StreamWriter(HopeLoveMindPath + NonBaseConceptString_InitialFilename, true, MyEncoding);
            sw.Write("\r\n" + newWord.ToString());
            sw.Flush();
            sw.Close();
        }

        private void WriteBaseFile(Word_ID newWord)
        {
            StreamWriter sw = new StreamWriter(HopeLoveMindPath + BaseConceptsStringFilename, true, MyEncoding);
            sw.Write("\r\n" + newWord.ToString());
            sw.Flush();
            sw.Close();
        }

        private void WriteConnnectionFile(Word_ID newWord,Word_ID toWord, List<Word_ID> mods)
        {
            StreamWriter sw = new StreamWriter(HopeLoveMindPath + ConceptConnections_InitialFilename, true, MyEncoding);

            string modStr="";
            mods.ForEach(m=>
            {
                if(modStr!="")
                {
                    modStr+=" ";
                }
                modStr += m.ToWeakString();
            });

            string outStr = "\r\n" + newWord.ToWeakString() + " to " + toWord.ToWeakString();
            if (modStr != "")
            {
                outStr+=" "+modStr;
            }

            sw.Write(outStr);
            sw.Flush();
            sw.Close();
        }

        private void CheckWordExisted(Word_ID newWord)
        {
            //检查新的Concept是否已经存在                      
            if (WordInList(newWord, _baseConcepts) || WordInList(newWord, _nonBaseConcepts))
            {
                throw new ApplicationException("The concept already exists!");
            }
        }

        private void CheckWordID(Word_ID newWord)
        {
            //检查ID是否现有的最大ID加1.
            int maxID_base = MaxID(newWord.word, _baseConcepts);
            int maxID_nonbase = MaxID(newWord.word, _nonBaseConcepts);
            int maxID = maxID_base > maxID_nonbase ? maxID_base : maxID_nonbase;
            if (newWord.id != maxID + 1)
            {
                throw new ApplicationException("The concept ID is not continuous!");
            }
        }

        private void CheckPOSUnique(Word_ID newWord)
        {
            List<Word_ID> wordNonBase = SearchWordOfSameStr(newWord.word, _nonBaseConcepts);
            List<Word_ID> wordBase = SearchWordOfSameStr(newWord.word, _baseConcepts);
            Word_ID samePos_NonBase = wordNonBase.Find(w => w.pos == newWord.pos); 
            Word_ID samePos_Base = wordBase.Find(w => w.pos == newWord.pos);

            if (samePos_Base != null || samePos_NonBase != null)
            {
                throw new ApplicationException("The POS is not unique!");
            }
        }

        private void CheckHasNoConnections(Word_ID newWord)
        {
            Connection_Info info=_connectionInfos.Find(c => c.me.WeakSame(newWord));
            if (info != null)
            {
                throw new ApplicationException("It has some connections!");
            }
        }

        private void CheckPos_Me_To(Word_ID newWord, Word_ID toWord)
        {
            Word_ID toWordSearch = SearchWordOfSameWordID_inTotalWord(toWord);
            if (toWordSearch != null)
            {
                if (toWordSearch.pos != newWord.pos && toWordSearch.pos != PartOfSpeech.Noun)
                {
                    throw new ApplicationException("The POS between new word and to word is not matched!!");
                }
            }
        }

        private Connection_Info SearchConnectionInfo(Word_ID w_i)
        {
            return _connectionInfos.Find(con => con.me.WeakSame(w_i));
        }

        private List<Word_ID> SearchWordOfSameStr(string str, List<Word_ID> list)
        {
            return list.FindAll(w_i => w_i.word == str);
        }

        private Word_ID SearchWordOfSameWordID_inTotalWord(Word_ID w_i)
        {
            Word_ID bRes=_baseConcepts.Find(bc => bc.WeakSame(w_i));
            Word_ID nbRes = _nonBaseConcepts.Find(nbc => nbc.WeakSame(w_i));

            if (bRes != null)
            {
                return bRes;
            }
            else if (nbRes != null)
            {
                return nbRes;
            }
            else
            {
                return null;
            }
        }

        private void button_CallWordTable_Click(object sender, RoutedEventArgs e)
        {
            if (_commonWordTable == null)
            {
                _commonWordTable = new CommonWordTable(GetWordWithConnection());
            }

            _commonWordTable.Left = this.Left + this.Width + 10;
            _commonWordTable.Owner = this;
            _commonWordTable.Show();
        }

        private List<string> GetWordWithConnection()
        {
            List<string> res=new List<string>();
            _connectionInfos.ForEach(c =>
            {
                res.Add(c.me.word);
            });

            return res;
        }
    }

    enum PartOfSpeech
    {
        Noun,
        Verb,
        Adjective,
        Numeral,
        Quantifier,
        Pronoun,
        Adverb,
        Preposition,
        Conjunction,
        Auxiliary,
        Onomatopoeia,
        Interjection,
        Ambiguous,
        Unknown,
        Puncture
    };

    class Word_ID
    {
        public string word;
        public int id;
        public PartOfSpeech pos = PartOfSpeech.Unknown;

        public bool Same(Word_ID w_i)
        {
            return word == w_i.word && id == w_i.id && pos == w_i.pos;
        }

        public bool WeakSame(Word_ID w_i)
        {
            return word == w_i.word && id == w_i.id ;
        }

        override public string ToString()
        {
            string res = "";
            res += id + " " + word+" "+(int)pos ;

            return res;
        }

        public string ToWeakString()
        {
            string res = "";
            res += id + " " + word ;

            return res;
        }
    }

    class Edge_Info
    {
        public Word_ID to = new Word_ID();
        public List<Word_ID> mods = new List<Word_ID>();
    }

    class Connection_Info
    {
        public Word_ID me = new Word_ID();
        public List<Edge_Info> edge_infos = new List<Edge_Info>();

        override public string ToString()
        {
            string res = "";
            res += me.ToString()+" " ;
            edge_infos.ForEach(edgeInfo =>
            {
                res+="to "+edgeInfo.to.ToString()+" ";
                edgeInfo.mods.ForEach(mod =>
                {
                    res += mod.ToString() + " ";
                });
            });

            return res;
        }

    }
}
