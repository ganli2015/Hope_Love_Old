using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;

namespace DataProcessor
{
    public class SegmentationCorpusExtractor
    {
        string rawdir = "../../../Corpus/Raw/";
        string newdir = "../../../Corpus/New/";


        public SegmentationCorpusExtractor()
        {
            
        }

        public void Run()
        {
            //Extract_DGK_Shooter();
            YuLiaoKuZaiXian ylkzx = new YuLiaoKuZaiXian() { newdir = this.newdir, rawdir = this.rawdir };
            ylkzx.Extract();
        }

        private void Extract_DGK_Shooter()
        {
            var rawSens = ReadRawSentences();
            OutputNewSentences(rawSens);
        }

        private List<string> ReadRawSentences()
        {
            string filename = rawdir + "dgk_shooter_z.conv";
            StreamReader sr = new StreamReader(filename,Encoding.UTF8);

            var res = new List<string>();
            while(!sr.EndOfStream)
            {
                string line = sr.ReadLine();
                if(line.Contains("M"))
                {
                    res.Add(line.Substring(line.IndexOf("M")+2));
                }
            }

            sr.Close();

            return res;
        }


        private void OutputNewSentences(List<string> raw)
        {
            string filename = newdir + "dgk_shooter_z.conv";
            StreamWriter sw = new StreamWriter(filename,false,Encoding.Unicode);

            foreach (var sen in raw)
            {
                string sen_noSeg = "";
                foreach (var ch in sen)
                {
                    if(ch!='/')
                    {
                        sen_noSeg += ch;
                    }
                }



                sw.WriteLine((sen_noSeg));
                sw.WriteLine((sen));
            }

            sw.Flush();
            sw.Close();
        }

        private string UnicodeToAnsi(string str)
        {
            byte[] byteunicode = Encoding.Unicode.GetBytes(str);
            string ASCIIstring = Encoding.ASCII.GetString(byteunicode);

            return ASCIIstring;
        }
    }

    class YuLiaoKuZaiXian
    {
        public string rawdir { get; set; }
        public string newdir { get; set; }

        List<string> _puncEndofSentence = new List<string>();

        public YuLiaoKuZaiXian()
        {
            _puncEndofSentence.Add("。");
            _puncEndofSentence.Add("！");
            _puncEndofSentence.Add("？");
            _puncEndofSentence.Add("：");
            _puncEndofSentence.Add("；");
            _puncEndofSentence.Add("…");
            _puncEndofSentence.Add("，");
        }

        public void Extract()
        {
            string filename_raw = rawdir + "corpus_de_raw.txt";
            StreamReader sr = new StreamReader(filename_raw, Encoding.UTF8);

            string filename_tag = rawdir + "corpus_de_segmented.txt";
            StreamReader sr_tag = new StreamReader(filename_tag, Encoding.UTF8);

            StreamWriter sw = new StreamWriter(newdir + "corpus_de.txt", false, Encoding.Unicode);

            int count = 0;
            while (!sr.EndOfStream && !sr_tag.EndOfStream)
            {
                string line1_whole = sr.ReadLine();
                string line2_whole= sr_tag.ReadLine();

                RemoveHeaderNumber(ref line1_whole);
                RemoveHeaderNumber(ref line2_whole);
                try
                {
                    CheckTableTag(line1_whole);
                    CheckTableTag(line2_whole);
                }
                catch (System.Exception ex)
                {
                    Console.WriteLine(ex.Message);
                    Console.ReadLine();
                }

                ReplaceDe(ref line1_whole);
                ReplaceDe(ref line2_whole);

                try
                {
                    CheckDe(line1_whole);
                    CheckDe(line2_whole);
                }
                catch (System.Exception ex)
                {
                    Console.WriteLine(ex.Message);
                    Console.ReadLine();
                }

                try
                {
                    var segForm = SegmentFormat(line2_whole);

                    List<string> line1_puncSplit = SplitWithPunc(line1_whole);
                    List<string> line2_puncSplit = SplitWithPunc(segForm);

                    if (line1_puncSplit.Count != line2_puncSplit.Count)
                    {
                        throw new Exception(line1_whole);
                    }

                    for (int i = 0; i < line1_puncSplit.Count; ++i)
                    {
                        sw.WriteLine(line1_puncSplit[i]);
                        sw.WriteLine(line2_puncSplit[i]);
                        ++count;
                    }
                }
                catch (System.Exception ex)
                {
                    Console.WriteLine(ex.Message);
                    continue;
                }
            }

            sw.Flush();
            sw.Close();

            Console.WriteLine(count);
            Console.ReadLine();
        }

        private void RemoveHeaderNumber(ref string line)
        {
            line = line.Substring(line.IndexOf("\t") + 2);
        }

        private void ReplaceDe(ref string line)
        {
            line=line.Replace(" [的] ", "的");
        }

        private void CheckTableTag(string line)
        {
            if(line.Contains('\t'))
            {
                throw new Exception(line);
            }
        }

        private void CheckDe(string line)
        {
            if (line.Contains("[的]"))
            {
                throw new Exception(line);
            }
        }

        private string SegmentFormat(string line)
        {
            var split = line.Split(' ');
            string res = "";

            foreach(var str in split)
            {
                if (str == "") continue;

                int slopeIndex = str.IndexOf('/');
                if(slopeIndex>=0)
                {
                    res += str.Substring(0, slopeIndex+1);
                }
                else
                {
                    throw new Exception(line);
                }
            }

            return res.Substring(0, res.LastIndexOf('/'));
        }

        private List<string> SplitWithPunc(string line)
        {
            List<string> res = new List<string>();

            int startIndex = 0;
            while(startIndex<line.Length)
            {
                string remainStr = line.Substring(startIndex);
                int puncIndex = IndexOfPunc(remainStr);
                if(puncIndex>=0)
                {
                    res.Add(line.Substring(startIndex, puncIndex + 1));
                    startIndex += puncIndex + 1;
                }
                else
                {
                    res.Add(line.Substring(startIndex));
                    break;
                }
            }

            return res;
        }

        //Get index of punctuation.
        private int IndexOfPunc(string line)
        {
            int res = int.MaxValue;
            foreach (var punc in _puncEndofSentence)
            {
                int firstIndex = line.IndexOf(punc);
                if(firstIndex>=0 && firstIndex<res)
                {
                    if (firstIndex!=line.Length-1 && line[firstIndex + 1] == '/')
                    {
                        //line is segmentation form.
                        res = firstIndex+1;
                    }
                    else
                    {
                        res = firstIndex;
                    }
                }
            }

            if(res==int.MaxValue)
            {
                return -1;
            }
            else
            {
                return res;
            }
        }
    }
}
