using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;
using System.Diagnostics;

namespace DataProcessor
{
    public class SegmentationCorpusExtractor
    {
        public SegmentationCorpusExtractor()
        {
            
        }

        public void Run()
        {
            //Extract_DGK_Shooter();
            YuLiaoKuZaiXian ylkzx = new YuLiaoKuZaiXian() { };
            //            ylkzx.Extract();
            //           ylkzx.ExtractGrammarSample();
            ylkzx.StatWordsCountDistribution();
        }

        private void Extract_DGK_Shooter()
        {
            var rawSens = ReadRawSentences();
            OutputNewSentences(rawSens);
        }

        private List<string> ReadRawSentences()
        {
            string filename = Dir.rawdir + "dgk_shooter_z.conv";
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
            string filename = Dir.newdir + "dgk_shooter_z.conv";
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
        struct POSInfo
        {
            public string Name { get; set; }
            public PartOfSpeech POS { get; set; }
        }

        List<string> _puncEndofSentence = new List<string>();

        Dictionary<string, POSInfo> POSTable = new Dictionary<string, POSInfo>();

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

        private void InitPOSTable()
        {
            using (StreamReader sr = new StreamReader(Dir.rawdir +"tag.txt", Encoding.Default))
            {
                while(!sr.EndOfStream)
                {
                    string line = sr.ReadLine();
                    var split = line.Split(' ');
                    int pos = Convert.ToInt32(split[2]);
                    POSTable.Add(split[0],new POSInfo() { Name = split[1], POS = (PartOfSpeech)pos });
                }
            }
        }

        //Have searched corpus containing "的".
        public void Extract()
        {
            InitPOSTable();
            GenerateSegementFile();
        }

        private void GenerateSegementFile()
        {
            string filename_raw = Dir.rawdir + "corpus_de_raw.txt";
            StreamReader sr = new StreamReader(filename_raw, Encoding.UTF8);

            string filename_tag = Dir.rawdir + "corpus_de_segmented.txt";
            StreamReader sr_tag = new StreamReader(filename_tag, Encoding.UTF8);

            StreamWriter sw = new StreamWriter(Dir.newdir + "corpus_de.txt", false, Encoding.Unicode);
            StreamWriter sw_pos = new StreamWriter(Dir.newdir + "corpus_de_pos.txt", false, Encoding.Unicode);

            int count = 0;
            while (!sr.EndOfStream && !sr_tag.EndOfStream)
            {
                string line1_whole = sr.ReadLine();
                string line2_whole = sr_tag.ReadLine();

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
                    var posForm = SegmentPOSFormat(line2_whole);

                    //Split long sentence into short sentences.
                    List<string> line1_puncSplit = SplitWithPunc(line1_whole);
                    List<string> line2_puncSplit = SplitWithPunc(segForm);
                    List<string> line3_puncSplit = SplitWithPunc(posForm,true);

                    if (line1_puncSplit.Count != line2_puncSplit.Count || line3_puncSplit.Count != line2_puncSplit.Count)
                    {
                        throw new Exception(line1_whole);
                    }

                    for (int i = 0; i < line1_puncSplit.Count; ++i)
                    {

                        sw.WriteLine(line1_puncSplit[i]);
                        sw.WriteLine(line2_puncSplit[i]);

                        if (!EndWithPunc(line3_puncSplit[i]))
                        {
                            Console.WriteLine("Not end with Punctuation: " + line3_puncSplit[i]);
                            continue;
                        }

                        sw_pos.WriteLine(line1_puncSplit[i]);
                        sw_pos.WriteLine(line3_puncSplit[i]);

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
            sw_pos.Flush();
            sw_pos.Close();

            sr.Close();
            sr_tag.Close();

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

        private bool EndWithPunc(string line)
        {
            if(line.LastIndexOf("/14")!=line.Length-3)
            {
                return false;
            }
            else
            { return true; }
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

            return res.Substring(0, res.LastIndexOf('/')+1);
        }

        private string SegmentPOSFormat(string line)
        {
            var split = line.Split(' ');
            string res = "";

            for (int i=0;i< split.Length;++i)
            {
                if(split[i]=="") continue;

                var slopeSplit = split[i].Split('/');
                Debug.Assert(slopeSplit.Length == 2);
                Debug.Assert(POSTable.ContainsKey(slopeSplit[1]));

                PartOfSpeech pos = POSTable[slopeSplit[1]].POS;
                if(pos==PartOfSpeech.Other)
                {
                    throw new Exception("Contain other.");
                }

                int posIndex = Convert.ToInt32(pos);

                res += slopeSplit[0] +"/"+ Convert.ToString(posIndex);
                if(i!=split.Length-1)
                {
                    res += " ";
                }
            }

            return res;
        }

        private List<string> SplitWithPunc(string line,bool POSFormat=false)
        {
            List<string> res = new List<string>();

            int startIndex = 0;
            while(startIndex<line.Length)
            {
                string remainStr = line.Substring(startIndex);
                if(remainStr==" ") break;

                int puncIndex = IndexOfPunc(remainStr, POSFormat);

                if(puncIndex>=0)
                {
                    res.Add(line.Substring(startIndex, puncIndex + 1).Trim());
                    startIndex += puncIndex + 1;
                }
                else
                {
                    res.Add(line.Substring(startIndex).Trim());
                    break;
                }
            }

            return res;
        }

        //Get index of the blank after punctuation.
//         private int IndexOfPunc_POS(string line)
//         {
//             return line.IndexOf("/14") + 3;
//         }

        //If line is not of POS format,get index of the slope after punctuation.
        //If line is of POS format, get the index of the number after slope.
        private int IndexOfPunc(string line, bool POSFormat = false)
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
                if(!POSFormat)
                {
                    return res;
                }
                else
                {
                    return res + 2;
                }
            }
        }

        //Generate grammar sequences based on "corpus_de_pos.txt".
        public void ExtractGrammarSample()
        {
            string filename = Dir.newdir + "corpus_de_pos.txt";
            string outFile = "str_sample_corpus_de.txt";
            StreamReader sr = new StreamReader(filename, Encoding.Unicode);
            StreamWriter sw = new StreamWriter(outFile, false, Encoding.ASCII);

            while(!sr.EndOfStream)
            {
                //skip the raw sentence.
                sr.ReadLine();
                string line = sr.ReadLine();

                var blankSplit = line.Split(' ');

                try
                {
                    //collect indexes of POS.
                    List<string> posIntList = new List<string>();
                    foreach (var word in blankSplit)
                    {
                        var slopeSplit = word.Split('/');
                        Debug.Assert(slopeSplit.Length == 2);
                        posIntList.Add(slopeSplit[1]);
                    }

                    sw.Write(posIntList.Count);
                    foreach (var index in posIntList)
                    {
                        sw.Write(" " + index);
                    }
                    sw.WriteLine("");
                }
                catch (System.Exception ex)
                {
                    Console.WriteLine(ex.Message);
                    continue;
                }
                
            }

            sw.Flush();
            sw.Close();
            sr.Close();

            File.Copy(outFile, Dir.outdir + outFile,true);
        }

        public void StatWordsCountDistribution()
        {
            string filename = Dir.newdir + "corpus_de_pos.txt";
            string outFile = "WordCountDistribtion.csv";
            StreamReader sr = new StreamReader(filename, Encoding.Unicode);
            StreamWriter sw = new StreamWriter(outFile, false, Encoding.ASCII);

            SortedDictionary<int, int> countDistri = new SortedDictionary<int, int>();

            while (!sr.EndOfStream)
            {
                string line = sr.ReadLine();
                sr.ReadLine();

                int length = line.Length;
                if(countDistri.ContainsKey(length))
                {
                    countDistri[length]++;
                }
                else
                {
                    countDistri.Add(length,1);
                }
            }


            foreach ( var pair in countDistri)
            {
                sw.WriteLine(pair.Key + "," + pair.Value);
            }

            sw.Flush();
        }
    }
}
