namespace StartForm
{
    partial class MainForm
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.Button_Hope_Love = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // Button_Hope_Love
            // 
            this.Button_Hope_Love.Location = new System.Drawing.Point(30, 25);
            this.Button_Hope_Love.Name = "Button_Hope_Love";
            this.Button_Hope_Love.Size = new System.Drawing.Size(79, 30);
            this.Button_Hope_Love.TabIndex = 0;
            this.Button_Hope_Love.Text = "Hope_Love";
            this.Button_Hope_Love.UseVisualStyleBackColor = true;
            this.Button_Hope_Love.Click += new System.EventHandler(this.Button_Hope_Love_Click);
            // 
            // MainForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(284, 262);
            this.Controls.Add(this.Button_Hope_Love);
            this.Name = "MainForm";
            this.Text = "MainForm";
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Button Button_Hope_Love;
    }
}