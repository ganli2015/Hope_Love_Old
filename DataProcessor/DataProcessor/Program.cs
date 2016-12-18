using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using HopeLove;

namespace DataProcessor
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
        Ambiguous,//Ambiguous indicates a word is known by AI but has no definite POS temporarily.
        Unknown,//Unknown indicates a word is unknown.
        Punctuation,
        Other
    };

    class Program
    {
        static void Main(string[] args)
        {


            //             POSAssignment posAssign = new POSAssignment();
            //             posAssign.AssignPOSofCommonWords();

            //             SegmentationCorpusExtractor sce = new SegmentationCorpusExtractor();
            //             sce.Run();

            ReduceGrammarPatternDistribution rgpd = new ReduceGrammarPatternDistribution();
            rgpd.Run(Dir.outdir+"GrammaPatterns_Initial_corpus_de.txt", Dir.outdir + "GrammaPatterns_Initial_corpus_de_reduced.txt");
        }
    }
}
