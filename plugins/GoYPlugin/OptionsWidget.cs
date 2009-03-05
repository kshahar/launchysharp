using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Text;
using System.Windows.Forms;

namespace GoYPlugin
{
    public partial class OptionsWidget : UserControl
    {
        public OptionsWidget()
        {
            InitializeComponent();
        }

        public bool isCaseSensitiveChecked
        {
            get
            {
                return caseSensitiveCheckBox.Checked;
            }
            set
            {
                caseSensitiveCheckBox.Checked = value;
            }
        }    
    }
}
