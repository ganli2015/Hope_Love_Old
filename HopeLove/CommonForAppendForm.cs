using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace HopeLove
{

    public enum PartOfSpeech
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

    public class Word_ID
    {
        public string word;
        public int id;
        public PartOfSpeech pos = PartOfSpeech.Unknown;

        public bool Same(Word_ID w_i)
        {
            return word == w_i.word && id == w_i.id && pos == w_i.pos;
        }

        /// <summary>
        /// Ignore the difference of POS
        /// </summary>
        /// <param name="w_i"></param>
        /// <returns></returns>
        public bool WeakSame(Word_ID w_i)
        {
            return word == w_i.word && id == w_i.id;
        }

        override public string ToString()
        {
            string res = "";
            res += id + " " + word + " " + (int)pos;

            return res;
        }

        public string ToWeakString()
        {
            string res = "";
            res += id + " " + word;

            return res;
        }
    }


    public class CommonForAppendForm
    {
        public static Word_ID StringToWordID(string str)
        {
            string[] sp = str.Split(' ');
            if (sp.Length != 2)
            {
                throw new ArgumentOutOfRangeException("StringToWordID");
            }

            Word_ID res = new Word_ID();
            res.id = Convert.ToInt32(sp[0]);
            res.word = sp[1];

            return res;
        }

        public static List<string> RemoveBlank(string[] strs)
        {
            List<string> res = new  List<string>();
            foreach (string s in strs)
            {
                if (s != "")
                {
                    res.Add(s);
                }
            }

            return res;
        }
    }
}
