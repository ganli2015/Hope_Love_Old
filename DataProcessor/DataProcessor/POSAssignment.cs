using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;

namespace DataProcessor
{
    /// <summary>
    /// Assign POS to words
    /// </summary>
    public class POSAssignment
    {
        const string appDataDir = @"..\..\..\..\HopeLove\bin\Debug\HopeLoveData\";
        const string mindDataDir = @"..\..\..\..\Mind\HopeLoveData\";

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
        };

        /// <summary>
        /// Mapping from some string letters to POS. Used for reading "ChineseDict.txt"
        /// </summary>
        Dictionary<string, PartOfSpeech> posTable;

        public POSAssignment()
        {
            InitPOSTable();
        }

        public void AssignPOSofCommonWords()
        {
            var commonWords = ReadCommonWords();
            var ChineseDict = ReadChineseDict();
            var wordPOS = GeneratePOSDict(commonWords, ChineseDict);
            OutputPOSDict(wordPOS);


        }

        private void InitPOSTable()
        {
            posTable = new Dictionary<string, PartOfSpeech>();

            posTable.Add("n", PartOfSpeech.Noun);
            posTable.Add("v", PartOfSpeech.Verb);
            posTable.Add("i", PartOfSpeech.Adjective);
            posTable.Add("a", PartOfSpeech.Adjective);
            posTable.Add("m", PartOfSpeech.Numeral);
            posTable.Add("q", PartOfSpeech.Quantifier);
            posTable.Add("r", PartOfSpeech.Pronoun);
            posTable.Add("d", PartOfSpeech.Adverb);
            posTable.Add("t", PartOfSpeech.Adverb);
            posTable.Add("p", PartOfSpeech.Preposition);
            posTable.Add("c", PartOfSpeech.Conjunction);
            posTable.Add("u", PartOfSpeech.Auxiliary);
            posTable.Add("o", PartOfSpeech.Onomatopoeia);
            posTable.Add("y", PartOfSpeech.Interjection);
            posTable.Add("e", PartOfSpeech.Interjection);

        }

        private List<string> ReadCommonWords()
        {
            string filename = appDataDir + "IDF of Common Words.txt";
            StreamReader sr = new StreamReader(filename,Encoding.Default);

            List<string> res = new List<string>();
            while(!sr.EndOfStream)
            {
                string line = sr.ReadLine();
                res.Add(line.Split(' ')[0]);
            }

            return res;
        }

        private Dictionary<string,List<string>> ReadChineseDict()
        {
            string filename = appDataDir + "ChineseDict.txt";
            StreamReader sr = new StreamReader(filename, Encoding.Default);

            Dictionary<string, List<string>> res = new Dictionary<string, List<string>>();
            while (!sr.EndOfStream)
            {
                string line = sr.ReadLine();
                string[] split = line.Split(',');

                if(split.Length<=1)
                {
                    throw new ArgumentOutOfRangeException();
                }

                List<string> pos = split.ToList();
                pos.Remove(pos[0]);
                res.Add(split[0], pos);
            }

            return res;
        }


        private Dictionary<string, List<PartOfSpeech>> GeneratePOSDict(List<string> commonWords, Dictionary<string, List<string>> ChineseDict)
        {
            Dictionary<string, List<PartOfSpeech>> res = new Dictionary<string, List<PartOfSpeech>>();
            foreach (var word in commonWords)
            {
                if (!ChineseDict.ContainsKey(word))
                {
                    Console.WriteLine("Cannot find {0} in ChineseDict.", word);
                    continue;
                }

                List<string> posesStr = ChineseDict[word];
                List<PartOfSpeech> poses = new List<PartOfSpeech>();
                //Find corresponding POS from POS string.
                posesStr.ForEach(pos =>
                {
                    if (posTable.ContainsKey(pos))
                    {
                        poses.Add(posTable[pos]);
                    }
                });

                if (poses.Count == 0)
                {
                    Console.WriteLine("Cannot find POS of {0} .", word);
                    continue;
                }

                res.Add(word, poses);
            }

            return res;
        }

        private void OutputPOSDict(Dictionary<string, List<PartOfSpeech>> posDict)
        {
            string filename = appDataDir + "BaseConceptsString2.txt";
            StreamWriter sw = new StreamWriter(filename,false, Encoding.Default);

            foreach(var dict in posDict)
            {
                HashSet<PartOfSpeech> existPOS = new HashSet<PartOfSpeech>();

                //ID for the same word.
                int index = 0;
                foreach (var pos in dict.Value)
                {
                    if(existPOS.Contains(pos))
                    {
                        continue;
                    }

                    sw.Write(index++);
                    sw.Write(" ");
                    sw.Write(dict.Key);
                    sw.Write(" ");
                    sw.Write(Convert.ToInt32(pos));
                    sw.Write("\r\n");

                    existPOS.Add(pos);
                }
            }

            sw.Flush();
            sw.Close();

            File.Copy(filename, mindDataDir + "BaseConceptsString2.txt", true);
        }

    }
}
