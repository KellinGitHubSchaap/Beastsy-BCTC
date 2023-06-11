#pragma once

#include "../BitmapConverter/include/bitmap_converter.h"

namespace BitmapConverter {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;


	public ref class Beastsy : public System::Windows::Forms::Form
	{
	public:

		bool isDragging = false;
		int lastX, lastY;
		String^ currentImageFilePath;

	public:
	private: System::Windows::Forms::ToolStripMenuItem^ toolStripMenuItem1;
	private: System::Windows::Forms::ToolStripMenuItem^ toolStripMenuItem2;
	private: System::Windows::Forms::ToolStripButton^ ImportButton;
	private: System::Windows::Forms::OpenFileDialog^ ImportBMPDialog;
	private: System::Windows::Forms::SaveFileDialog^ SaveFileDialog;




	private: System::Windows::Forms::ToolStripDropDownButton^ toolStripButton1;

	public:

		Beastsy(void)
		{
			InitializeComponent();

			System::String^ username = System::Environment::GetEnvironmentVariable("USERNAME");
			ImportBMPDialog->InitialDirectory = "C:\\Users\\" + username + "\\Pictures";

			ImagePreviewBox->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &Beastsy::Beastsy_MouseDown);
			ImagePreviewBox->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &Beastsy::Beastsy_MouseMove);
			ImagePreviewBox->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &Beastsy::Beastsy_MouseUp);
		}

		System::Int32 Clamp(int value, int min, int max);
		System::Drawing::Bitmap^ ScaleImage(System::Drawing::Bitmap^ image, int width, int height);
		System::Void SetupImage(System::Drawing::Image^ selectedImage);
	private: System::Windows::Forms::Panel^ ImagePreviewHolder;
	public:




	private:
		System::Void Beastsy_MouseDown(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e)
		{
			if (e->Button == System::Windows::Forms::MouseButtons::Left)
			{
				isDragging = true;
				lastX = e->X;
				lastY = e->Y;
			}
		}

		System::Void Beastsy_MouseMove(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e)
		{
			if (!isDragging) return;

			// Check if the mouse has moved from the previous position
			if (e->X != lastX || e->Y != lastY)
			{
				// Calculate the delta movement
				int deltaX = (e->X - lastX) / 1.25f;
				int deltaY = (e->Y - lastY) / 1.25f;

				// Calculate the new position
				int newX = Clamp(ImagePreviewBox->Location.X + deltaX, -ImagePreviewBox->Image->Size.Width + ImagePreviewHolder->Width, 0);
				int newY = Clamp(ImagePreviewBox->Location.Y + deltaY, -ImagePreviewBox->Image->Size.Height + ImagePreviewHolder->Height, 0);

				//// Update the picture's position
				ImagePreviewBox->Location = Point(newX, newY);

				// Update the previous mouse coordinates
				lastX = e->X;
				lastY = e->Y;
			}
		}

		// MouseUp event handler
		System::Void Beastsy_MouseUp(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e)
		{
			if (e->Button == System::Windows::Forms::MouseButtons::Left)
			{
				isDragging = false;
				lastX = 0;
				lastY = 0;
			}
		}
	private: System::Windows::Forms::PictureBox^ ImagePreviewBox;





	protected:
		~Beastsy()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::ToolStrip^ MenuToolStrip;
	protected:

	private: System::Windows::Forms::ToolStripButton^ ConvertButton;
	protected:





	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(Beastsy::typeid));
			this->MenuToolStrip = (gcnew System::Windows::Forms::ToolStrip());
			this->ImportButton = (gcnew System::Windows::Forms::ToolStripButton());
			this->ConvertButton = (gcnew System::Windows::Forms::ToolStripButton());
			this->ImagePreviewBox = (gcnew System::Windows::Forms::PictureBox());
			this->ImagePreviewHolder = (gcnew System::Windows::Forms::Panel());
			this->toolStripMenuItem1 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolStripMenuItem2 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolStripButton1 = (gcnew System::Windows::Forms::ToolStripDropDownButton());
			this->ImportBMPDialog = (gcnew System::Windows::Forms::OpenFileDialog());
			this->SaveFileDialog = (gcnew System::Windows::Forms::SaveFileDialog());
			this->MenuToolStrip->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->ImagePreviewBox))->BeginInit();
			this->ImagePreviewHolder->SuspendLayout();
			this->SuspendLayout();
			// 
			// MenuToolStrip
			// 
			this->MenuToolStrip->GripStyle = System::Windows::Forms::ToolStripGripStyle::Hidden;
			this->MenuToolStrip->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->ImportButton,
					this->ConvertButton
			});
			this->MenuToolStrip->Location = System::Drawing::Point(0, 0);
			this->MenuToolStrip->Name = L"MenuToolStrip";
			this->MenuToolStrip->RenderMode = System::Windows::Forms::ToolStripRenderMode::System;
			this->MenuToolStrip->Size = System::Drawing::Size(634, 25);
			this->MenuToolStrip->TabIndex = 0;
			this->MenuToolStrip->Text = L"MenuStrip";
			// 
			// ImportButton
			// 
			this->ImportButton->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Text;
			this->ImportButton->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"ImportButton.Image")));
			this->ImportButton->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->ImportButton->Name = L"ImportButton";
			this->ImportButton->Size = System::Drawing::Size(47, 22);
			this->ImportButton->Text = L"Import";
			this->ImportButton->Click += gcnew System::EventHandler(this, &Beastsy::ImportButton_Click);
			// 
			// ConvertButton
			// 
			this->ConvertButton->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Text;
			this->ConvertButton->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"ConvertButton.Image")));
			this->ConvertButton->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->ConvertButton->Name = L"ConvertButton";
			this->ConvertButton->Size = System::Drawing::Size(53, 22);
			this->ConvertButton->Text = L"Convert";
			this->ConvertButton->Click += gcnew System::EventHandler(this, &Beastsy::ConvertButton_Click);
			// 
			// ImagePreviewBox
			// 
			this->ImagePreviewBox->BackColor = System::Drawing::SystemColors::ControlDark;
			this->ImagePreviewBox->BackgroundImageLayout = System::Windows::Forms::ImageLayout::None;
			this->ImagePreviewBox->Location = System::Drawing::Point(-3, -3);
			this->ImagePreviewBox->Margin = System::Windows::Forms::Padding(0);
			this->ImagePreviewBox->Name = L"ImagePreviewBox";
			this->ImagePreviewBox->Size = System::Drawing::Size(500, 500);
			this->ImagePreviewBox->SizeMode = System::Windows::Forms::PictureBoxSizeMode::AutoSize;
			this->ImagePreviewBox->TabIndex = 1;
			this->ImagePreviewBox->TabStop = false;
			// 
			// ImagePreviewHolder
			// 
			this->ImagePreviewHolder->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->ImagePreviewHolder->Controls->Add(this->ImagePreviewBox);
			this->ImagePreviewHolder->Location = System::Drawing::Point(75, 50);
			this->ImagePreviewHolder->Name = L"ImagePreviewHolder";
			this->ImagePreviewHolder->Size = System::Drawing::Size(500, 500);
			this->ImagePreviewHolder->TabIndex = 2;
			// 
			// toolStripMenuItem1
			// 
			this->toolStripMenuItem1->Name = L"toolStripMenuItem1";
			this->toolStripMenuItem1->Size = System::Drawing::Size(110, 22);
			this->toolStripMenuItem1->Text = L"Import";
			// 
			// toolStripMenuItem2
			// 
			this->toolStripMenuItem2->Name = L"toolStripMenuItem2";
			this->toolStripMenuItem2->Size = System::Drawing::Size(110, 22);
			this->toolStripMenuItem2->Text = L"Export";
			// 
			// toolStripButton1
			// 
			this->toolStripButton1->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Text;
			this->toolStripButton1->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->toolStripMenuItem1,
					this->toolStripMenuItem2
			});
			this->toolStripButton1->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->toolStripButton1->Name = L"toolStripButton1";
			this->toolStripButton1->Size = System::Drawing::Size(38, 22);
			this->toolStripButton1->Text = L"File";
			// 
			// Beastsy
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(634, 561);
			this->Controls->Add(this->ImagePreviewHolder);
			this->Controls->Add(this->MenuToolStrip);
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->MaximizeBox = false;
			this->MaximumSize = System::Drawing::Size(650, 600);
			this->MinimumSize = System::Drawing::Size(650, 600);
			this->Name = L"Beastsy";
			this->Text = L"Beastsy (BCTC)";
			this->MenuToolStrip->ResumeLayout(false);
			this->MenuToolStrip->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->ImagePreviewBox))->EndInit();
			this->ImagePreviewHolder->ResumeLayout(false);
			this->ImagePreviewHolder->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void ImportButton_Click(System::Object^ sender, System::EventArgs^ e)
	{
		ImportBMPDialog->Filter = "Bitmap Files (*.bmp)|*.bmp";
		ImportBMPDialog->ShowDialog();

		System::String^ selectedFilePath = ImportBMPDialog->FileName;

		if (!System::String::IsNullOrEmpty(selectedFilePath))
		{
			SetupImage(System::Drawing::Image::FromFile(selectedFilePath));
			ImportBMPDialog->InitialDirectory = selectedFilePath;
			currentImageFilePath = selectedFilePath;
		}
	}

	private: System::Void ConvertButton_Click(System::Object^ sender, System::EventArgs^ e)
	{
		if (ImagePreviewBox->Image == nullptr) return;

		int lastIndex = currentImageFilePath->LastIndexOf("\\");
		String^ filePathWithExtension = currentImageFilePath->Substring(lastIndex + 1);
		String^ filePathWithoutExtension = Path::GetFileNameWithoutExtension(filePathWithExtension);

		SaveFileDialog->FileName = filePathWithoutExtension + ".h";
		SaveFileDialog->Filter = "Header Files (*.h) | *.h";
		if(SaveFileDialog->ShowDialog() != System::Windows::Forms::DialogResult::OK) return;

		System::String^ selectedOutputPath = SaveFileDialog->FileName;

		ConvertBitmap(currentImageFilePath, selectedOutputPath, filePathWithoutExtension);
	}
	};
}
