using System;
using System.Drawing;
using System.Collections;
using System.ComponentModel;
using System.Windows.Forms;

namespace FullSailAFI.GamePlaying
{
	/// <summary>
	/// Summary description for ConfirmDialog.
	/// </summary>
	public class ConfirmDialog : System.Windows.Forms.Form
	{
		private System.Windows.Forms.Label messageLabel;
		private System.Windows.Forms.Button yesButton;
		private System.Windows.Forms.Button noButton;

		/// <summary>
		/// Required designer variable.
		/// </summary>
		private System.ComponentModel.Container components = null;

		public ConfirmDialog(string s)
		{
			//
			// Required for Windows Form Designer support
			//
			InitializeComponent();

			//
			// TODO: Add any constructor code after InitializeComponent call
			//

			this.messageLabel.Text = s;
		}

		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		protected override void Dispose( bool disposing )
		{
			if( disposing )
			{
				if(components != null)
				{
					components.Dispose();
				}
			}
			base.Dispose( disposing );
		}

		#region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		private void InitializeComponent()
		{
			this.messageLabel = new System.Windows.Forms.Label();
			this.yesButton = new System.Windows.Forms.Button();
			this.noButton = new System.Windows.Forms.Button();
			this.SuspendLayout();
			// 
			// messageLabel
			// 
			this.messageLabel.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Left | System.Windows.Forms.AnchorStyles.Right)));
			this.messageLabel.Location = new System.Drawing.Point(16, 24);
			this.messageLabel.Name = "messageLabel";
			this.messageLabel.Size = new System.Drawing.Size(186, 16);
			this.messageLabel.TabIndex = 0;
			this.messageLabel.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
			// 
			// yesButton
			// 
			this.yesButton.DialogResult = System.Windows.Forms.DialogResult.Yes;
			this.yesButton.Location = new System.Drawing.Point(29, 64);
			this.yesButton.Name = "yesButton";
			this.yesButton.TabIndex = 2;
			this.yesButton.Text = "Yes";
			// 
			// noButton
			// 
			this.noButton.DialogResult = System.Windows.Forms.DialogResult.No;
			this.noButton.Location = new System.Drawing.Point(115, 64);
			this.noButton.Name = "noButton";
			this.noButton.TabIndex = 1;
			this.noButton.Text = "No";
			// 
			// ConfirmDialog
			// 
			this.AcceptButton = this.yesButton;
			this.AutoScaleBaseSize = new System.Drawing.Size(5, 13);
			this.CancelButton = this.noButton;
			this.ClientSize = new System.Drawing.Size(218, 94);
			this.ControlBox = false;
			this.Controls.Add(this.noButton);
			this.Controls.Add(this.yesButton);
			this.Controls.Add(this.messageLabel);
			this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog;
			this.MaximizeBox = false;
			this.MinimizeBox = false;
			this.Name = "ConfirmDialog";
			this.ShowInTaskbar = false;
			this.StartPosition = System.Windows.Forms.FormStartPosition.CenterParent;
			this.Text = "Confirm";
			this.ResumeLayout(false);

		}
		#endregion
	}
}
