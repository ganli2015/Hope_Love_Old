using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;

namespace DataProcessor
{
    /// <summary>
    /// Reduce the scale of Grammar Pattern Distribution in "GrammaPatterns_Initial.txt".
    /// </summary>
    public class ReduceGrammarPatternDistribution
    {
        struct DistriInfo
        {
            public string line;
            public int freq;
        }

        List<DistriInfo> distri = new List<DistriInfo>();

        public void Run(string filename_raw,string file_reduced)
        {
            var meanFreq = ComputeMeanFrequence(filename_raw);
            Console.WriteLine(meanFreq);
            OutputReduced(meanFreq, file_reduced);
        }

        double ComputeMeanFrequence(string filename_raw)
        {
            Int64 total = 0;
            using (StreamReader sr = new StreamReader(filename_raw))
            {
                while(!sr.EndOfStream)
                {
                    string line = sr.ReadLine();
                    var split = line.Split(' ');
                    var freq = Convert.ToInt32(split[split.Length - 1]);

                    distri.Add(new DistriInfo() { line = line, freq = freq });
                    total += freq;
                }
                sr.Close();
            }

            return (double)total / distri.Count;
        }

        void OutputReduced(double meanFreq,string file_reduced)
        {
            using (StreamWriter sw = new StreamWriter(file_reduced, false))
            {
                foreach (var dis in distri)
                {
                    if(dis.freq> meanFreq)
                    {
                        sw.WriteLine(dis.line);
                    }
                }

                sw.Flush();
                sw.Close();
            }
        }
    }
}
