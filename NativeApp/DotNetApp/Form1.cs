using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Diagnostics;

namespace DotNetApp
{
    public partial class Form1 : Form
    {
        [DllImport("SharedMemory", EntryPoint = "ValidateVersion")]
        private static extern bool ValidateVersion(float version);

        [DllImport("SharedMemory", EntryPoint = "SetTestValue")]
        private static extern void SetTestValue(int index, int value);

        [DllImport("SharedMemory", EntryPoint = "GetTestValue")]
        private static extern int GetTestValue(int index);

        [DllImport("SharedMemory", EntryPoint = "GetBuffer", CallingConvention = CallingConvention.Cdecl)]
        private static extern IntPtr GetBuffer(int index);


        private Process m_process;
        private int m_bufferIndex = 1;
        private float[] m_buffer = new float[100 * 100 * 4];

        public Form1()
        {
            InitializeComponent();

            bool success = ValidateVersion(1.0f);
            SetTestValue(1, m_bufferIndex);

            m_process = Process.Start("NativeApp.exe");

            this.timer1.Start();
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            this.label2.Text = GetTestValue(0).ToString();
            this.label3.Text = GetTestValue(1).ToString();
            this.label4.Text = GetTestValue(2).ToString();
            this.label5.Text = GetTestValue(3).ToString();

            this.label1.Text = "";
            IntPtr data = GetBuffer(m_bufferIndex);
            Marshal.Copy(data, m_buffer, 0, m_buffer.Length);

            for (int index = 0; index < 15; ++index)
            {
                this.label1.Text += m_buffer[index].ToString() + ", ";
            }
        }
    }
}
