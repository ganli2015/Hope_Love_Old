using System;
using System.Collections.Generic;
using System.Linq;
using System.Data;
using System.Text;
using MySql.Data.MySqlClient;
using System.IO;

namespace MySQLDataBase
{
    class Program
    {
        static void Main(string[] args)
        {
            MySqlConnection connection = new MySqlConnection("Data Source=localhost;Initial Catalog=HopeLove;User ID=root;Password=gggggg");
            connection.Open();
            if (connection.State.ToString() == "Open")
            {
                Console.Write("Connection Success!\r\n");
            }

            //GrammaPatternDB(connection);
            ConceptStringDB(connection);

            DataTable table = new DataTable();
            DataRow row = new DataRow();
            
            
        }

        static void GrammaPatternDB(MySqlConnection connection)
        {
            MySqlParameter id, freq, pattern;
            MySqlCommand command = new MySqlCommand("insert into GrammaPatterns(id,frequency,pattern) values(?id,?frequency,?pattern)", connection);
            id = command.Parameters.Add("?id", MySqlDbType.Int32);
            freq = command.Parameters.Add("?frequency", MySqlDbType.Int64);
            pattern = command.Parameters.Add("?pattern", MySqlDbType.String);
            command.Prepare();

            FileStream fs = new FileStream("..\\..\\..\\..\\Mind\\HopeLove\\GrammaPatterns.txt", FileMode.Open);
            StreamReader sr = new StreamReader(fs);
            int i = 0;
            while (!sr.EndOfStream)
            {
                string line = sr.ReadLine();
                int count = 0, frequency = 0;
                string patternStr = "";
                toPatternInfo(line, ref count, ref frequency, ref patternStr);

                id.Value = i++;
                freq.Value = frequency;
                pattern.Value = patternStr;


                try
                {
                    command.ExecuteNonQuery();
                }
                catch (System.Exception ex)
                {
                    Console.WriteLine(ex.Message);
                }
            }
        }

        static void ConceptStringDB(MySqlConnection connection)
        {
            MySqlParameter name, POE;
            MySqlCommand command = new MySqlCommand("insert into ConceptString(name, POE) values(?name,?POE)", connection);
            name = command.Parameters.Add("?name", MySqlDbType.String);
            POE = command.Parameters.Add("?POE", MySqlDbType.Int16);
            command.Prepare();

            FileStream fs = new FileStream("..\\..\\..\\..\\Mind\\HopeLove\\ConceptString.txt", FileMode.Open);
            StreamReader sr = new StreamReader(fs,Encoding.Default);
            while (!sr.EndOfStream)
            {
                string line = sr.ReadLine();
                string nameStr = "";
                int poe = 0;
                toConceptStringInfo(line, ref nameStr, ref poe);

                name.Value = nameStr;
                POE.Value = poe;

                try
                {
                    command.ExecuteNonQuery();
                }
                catch (System.Exception ex)
                {
                    Console.WriteLine(ex.Message);
                }
            }
        }

        static void toPatternInfo(string str, ref int count, ref int freq, ref string pattern)
        {
            count = (int)str[0] - 48;
            int i = 1;
            int iter = count;
            while (iter > 0)
            {
                if ((int)str[i] == 32)
                {
                    i++;
                    continue;
                }
                else
                {
                    pattern += str[i] + " ";
                    i++;
                    iter--;
                }
            }

            ++i;

            List<int> freqList = new List<int>();
            while ((int)str[i] != 32)
            {
                freqList.Add((int)str[i] - 48);
                ++i;
            }
            freq = 0;
            for (int j = freqList.Count - 1; j >= 0; j--)
            {
                freq += Convert.ToInt32(freqList[j] * Math.Pow(10, freqList.Count - 1 - j));
            }
        }

        static void toConceptStringInfo(string str, ref string name, ref int POE)
        {
            name = ReadFirstString(str);
            string restStr = TrimmedFirst(str, name.Length);
            POE = ReadFirstInt(TrimmedFirstBlank(restStr));
        }

        static string ReadFirstString(string str)
        {
            string res = "";
            int i = 0;
            while (i<str.Length &&(int)str[i] != 32  )
            {
                res += str[i];
                i++;
            }

            return res;
        }

        static int ReadFirstInt(string str)
        {
            int i=0;
            List<int> intList = new List<int>();
            while ( i < str.Length &&　(int)str[i] != 32)
            {
                intList.Add((int)str[i] - 48);
                ++i;
            }
            int res = 0;
            for (int j = intList.Count - 1; j >= 0; j--)
            {
                res += Convert.ToInt32(intList[j] * Math.Pow(10, intList.Count - 1 - j));
            }

            return res;
        }

        static string TrimmedFirst(string str,int count)
        {
            string res = "";
            for (int i = count; i < str.Length;++i )
            {
                res += str[i];
            }

            return res;
        }

        static string TrimmedFirstBlank(string str)
        {
            int blankCount = 0;
            while (blankCount < str.Length && (int)str[blankCount] == 32  )
            {
                blankCount++;
            }

            return TrimmedFirst(str,blankCount);
        }
    }
}
