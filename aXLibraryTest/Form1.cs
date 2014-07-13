using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace aXLibraryTest
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            AutomationX.AX bla = new AutomationX.AX("Tannenbaum", "Status", "err");
            bla.OnStatus += bla_OnStatus;
            bla.OnError += bla_OnError;
            AutomationX.AXWriter writer = new AutomationX.AXWriter(bla);
            writer.WriteBool("Tannenbaum", "STATE", true);
            AutomationX.AXReader reader = new AutomationX.AXReader(bla);
            System.Collections.Generic.List<String> instanceNames = reader.GetInstanceNames("Aktor_1fach");
            MessageBox.Show(reader.GetInstanceRemark("Tannenbaum3"));
            MessageBox.Show(reader.GetVariableRemark("Tannenbaum", "STATE"));
            bla.Shutdown();
        }

        void bla_OnStatus(string statusText)
        {
            MessageBox.Show(statusText, "Status", MessageBoxButtons.OK, MessageBoxIcon.Information);
        }

        void bla_OnError(string errorText)
        {
            MessageBox.Show(errorText, "Error", MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
        }
    }
}
