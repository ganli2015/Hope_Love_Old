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
using System.Text.RegularExpressions;

namespace HopeLove
{
    /// <summary>
    /// CommonWordTable.xaml 的交互逻辑
    /// </summary>
    public partial class CommonWordTable : Window
    {
        const string WordTablePath = "HopeLoveData\\";
        const string CommonWordTableFilename = "现代汉语常用词汇表.txt";
        const string TotalWordTableFilename = "现代汉语词典（第五版）全文.txt";

        Dictionary<string,string> _totalWord;
        List<string> _commonWord;
        List<string> _wordsWithMeaning;

        public CommonWordTable(List<string> wordsWithMeaning)
        {
            InitializeComponent();

            _totalWord = new Dictionary<string, string>();
            _commonWord = new List<string>();
            _wordsWithMeaning = wordsWithMeaning;

            Init_TotalWord();
            Init_CommonWord();
        }

        private void Init_CommonWord()
        {
            StreamReader sr = new StreamReader(WordTablePath + CommonWordTableFilename);
            string all = sr.ReadToEnd();
            string[] each = all.Split('\t');
            foreach (string word in each)
            {
                TextBlock tb = GenerateBox(word);

                if (_totalWord.ContainsKey(word))
                {
                    listBox_CommonWord.Items.Add(tb);
                    _commonWord.Add(word);
                }
            }
        }

        private void Init_TotalWord()
        {
            StreamReader sr = new StreamReader(WordTablePath + TotalWordTableFilename);
            while (!sr.EndOfStream)
            {
                string line = sr.ReadLine();
                if (line.Contains('【') && line.Contains('】'))
                {
                    Regex reg = new Regex("【(.+)】");
                    GroupCollection gc = reg.Match(line).Groups;
                    string word = gc[1].Value;

                    _totalWord[word] = line;
                }
            }
        }

        private TextBlock GenerateBox(string word)
        {
            TextBlock tb = new TextBlock();
            tb.Width = listBox_CommonWord.Width;
            tb.Text = word;
            if (_wordsWithMeaning.Contains(word))
            {
                tb.Background = new SolidColorBrush(Color.FromRgb(0, 0, 0));
                tb.Foreground = new SolidColorBrush(Color.FromRgb(255, 255, 255));
            }

            return tb;
        }

        private void listBox_CommonWord_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            TextBlock tb = listBox_CommonWord.SelectedItem as TextBlock;
            if (tb == null) return;

            string selected = tb.Text;
            if (selected == "") return;

            DisplayMeaning(selected);

        }

        private void DisplayMeaning(string selected)
        {
            if (_totalWord.ContainsKey(selected))
            {
                textBlock_Meaning.Text = _totalWord[selected];
            }
            else
            {
                textBlock_Meaning.Text = "";
            }
        }

        override protected void OnClosing(System.ComponentModel.CancelEventArgs e)
        {
            this.Hide();
            e.Cancel = true;
        }

        private void button_Search_Click(object sender, RoutedEventArgs e)
        {
            string searchStr=textBox_Search.Text as string;
            if (searchStr == "") return;

            SearchWord(searchStr);
        }

        private void SearchWord(string searchStr)
        {
            listBox_Search.Items.Clear();
            var allSearch = _commonWord.FindAll(w => w.Contains(searchStr));
            allSearch.ForEach(w =>
            {
                TextBlock tb = GenerateBox(w);
                listBox_Search.Items.Add(tb);
            });
        }

        private void listBox_Search_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            TextBlock tb = listBox_Search.SelectedItem as TextBlock;
            if (tb == null) return;
            string selected = tb.Text;
            if (selected == "") return;

            DisplayMeaning(selected);
        }

        private void textBox_Search_KeyDown(object sender, KeyEventArgs e)
        {
            if (e.Key == Key.Enter)
            {
                string searchStr = textBox_Search.Text as string;
                if (searchStr == "") return;

                SearchWord(searchStr);
            }
        }

        private void listBox_Search_GotFocus(object sender, RoutedEventArgs e)
        {
            TextBlock tb = listBox_Search.SelectedItem as TextBlock;
            if (tb == null) return;
            string selected = tb.Text;
            if (selected == "") return;

            DisplayMeaning(selected);
        }

        private void listBox_CommonWord_GotFocus(object sender, RoutedEventArgs e)
        {
            TextBlock tb = listBox_CommonWord.SelectedItem as TextBlock;
            if (tb == null) return;
            string selected = tb.Text;
            if (selected == "") return;

            DisplayMeaning(selected);
        }
    }
}
