
#include "TFile.h"
#include "TTree.h"

//#include "TTreeReader.h"
//#include "TTreeReaderValue.h"

#include "TH1F.h"

#include "THStack.h"
#include "TLegend.h"

//#include "TTreePlayer.h"
#include "TStyle.h"
#include "TGaxis.h"
#include "TCanvas.h"
#include "TGraphErrors.h"
#include "TGraphAsymmErrors.h"
#include "TEfficiency.h"
#include <fstream>
#include <iostream>
#include <iomanip>
#include <iostream>

#include <vector>
#include "math.h"

#include <TMultiGraph.h>


using namespace std;

void setTDRStyle();


void QCD_PURITY(){
  /*
  int nb = 9;
  float BINS[10] = { 0.0, 200.0,  225.0,  250.0, 300.0,  350.0,  450.0,  600.0,  750.0, 900.0};
  */

  int nb = 8;
  float BINS[9] = { 0.0, 200.0,  225.0,  250.0, 300.0,  350.0,  450.0,  600.0, 900.0};

  int ni = 0.0;
  int nf = 900.0;

  cout << "working" << endl;
  setTDRStyle();

  TCanvas* c1 = new TCanvas("c1","c1",200,200,800,700);
  c1->SetGrid();
  //c1->DrawFrame(0,0,200,1.2);

  TFile *new_QCD_CR_C = TFile::Open("newDMF_newTightIso_LooseElectron_TightMuon/CR_C/QCD.root","READ");
  if (new_QCD_CR_C == 0) {
    printf("Error: cannot open QCD.root root file \n");
    return;
  }
  TFile *new_Data_CR_C = TFile::Open("newDMF_newTightIso_LooseElectron_TightMuon/CR_C/Data.root","READ");
  if (new_Data_CR_C == 0) {
    printf("Error: cannot open QCD_C.root root file \n");
    return;
  }
  TFile *old_QCD_CR_C = TFile::Open("oldDMF_oldTightIso_VERYLooseElectron_LOOSEMuon_withTrigger_TAUPOG_newTriggerSF/CR_C/QCD.root","READ");
  if (old_QCD_CR_C == 0) {
    printf("Error: cannot open QCD.root root file \n");
    return;
  }
  TFile *old_Data_CR_C = TFile::Open("oldDMF_oldTightIso_VERYLooseElectron_LOOSEMuon_withTrigger_TAUPOG_newTriggerSF/CR_C/Data.root","READ");
  if (old_Data_CR_C == 0) {
    printf("Error: cannot open QCD_C.root root file \n");
    return;
  }


  TH1F *ourTauID_QCD_CR_C = (TH1F*)new_QCD_CR_C->Get("NDiTauCombinations/DiTauReconstructableMass");
  TH1F *ourTauID_Data_CR_C = (TH1F*)new_Data_CR_C->Get("NDiTauCombinations/DiTauReconstructableMass");
  TH1F *TAUPOG_QCD_CR_C = (TH1F*)old_QCD_CR_C->Get("NDiTauCombinations/DiTauReconstructableMass");
  TH1F *TAUPOG_Data_CR_C = (TH1F*)old_Data_CR_C->Get("NDiTauCombinations/DiTauReconstructableMass");


  TH1F *H_ourTauID_QCD_CR_C = new TH1F("h_NUMB", "h_NUMB", nb, BINS);
  TH1F *H_ourTauID_Data_CR_C = new TH1F("h_DENB", "h_DENB", nb, BINS);
  TH1F *H_TAUPOG_QCD_CR_C = new TH1F("h_NUMB", "h_NUMB", nb, BINS);
  TH1F *H_TAUPOG_Data_CR_C = new TH1F("h_DENB", "h_DENB", nb, BINS);

  Int_t nbins   = ourTauID_QCD_CR_C->GetXaxis()->GetNbins(); 

  for (int b = 1; b <= H_ourTauID_QCD_CR_C->GetXaxis()->GetNbins(); b++ ){
    double num_ourTauID = 0; 
    double den_ourTauID = 0;
    double num_TAUPOG = 0;
    double den_TAUPOG = 0;

    for (int i = 1; i <= nbins; i++ ){
      if(((( ourTauID_QCD_CR_C->GetXaxis()->GetBinLowEdge(i)) + (ourTauID_QCD_CR_C->GetXaxis()->GetBinWidth(i))) <= ((H_ourTauID_QCD_CR_C->GetXaxis()->GetBinLowEdge(b))+ (H_ourTauID_QCD_CR_C->GetXaxis()->GetBinWidth(b)))) && ((( ourTauID_QCD_CR_C->GetXaxis()->GetBinLowEdge(i))+ (ourTauID_QCD_CR_C->GetXaxis()->GetBinWidth(i))) > ((H_ourTauID_QCD_CR_C->GetXaxis()->GetBinLowEdge(b))))){
	
	num_ourTauID += ourTauID_QCD_CR_C->GetBinContent(i);
	den_ourTauID += ourTauID_Data_CR_C->GetBinContent(i);
	num_TAUPOG += TAUPOG_QCD_CR_C->GetBinContent(i);
	den_TAUPOG += TAUPOG_Data_CR_C->GetBinContent(i);
	
      }else if( ( ourTauID_QCD_CR_C->GetXaxis()->GetBinLowEdge(i)) >= (H_ourTauID_QCD_CR_C->GetXaxis()->GetBinLowEdge(nb)+ (H_ourTauID_QCD_CR_C->GetXaxis()->GetBinWidth(nb))) && b==nb){//---- ELSE ES SOLO PARA EL OVERFLOW... SI SE NO QUIERE OVERFLOW (QUITAR ESTE ELSE)

	num_ourTauID += ourTauID_QCD_CR_C->GetBinContent(i);
	den_ourTauID += ourTauID_Data_CR_C->GetBinContent(i);
	num_TAUPOG += TAUPOG_QCD_CR_C->GetBinContent(i);
	den_TAUPOG += TAUPOG_Data_CR_C->GetBinContent(i);

      }else if( ( ourTauID_QCD_CR_C->GetXaxis()->GetBinLowEdge(i)) < (H_ourTauID_QCD_CR_C->GetXaxis()->GetBinLowEdge(1)+ (H_ourTauID_QCD_CR_C->GetXaxis()->GetBinWidth(1))) && b==1){//---- ELSE ES SOLO PARA EL UNDERFLOW... SI SE NO QUIERE OVERFLOW (QUITAR ESTE ELSE)

	num_ourTauID += ourTauID_QCD_CR_C->GetBinContent(i);
	den_ourTauID += ourTauID_Data_CR_C->GetBinContent(i);
	num_TAUPOG += TAUPOG_QCD_CR_C->GetBinContent(i);
	den_TAUPOG += TAUPOG_Data_CR_C->GetBinContent(i);
		
      }else{
	continue;
      }
      
      H_ourTauID_QCD_CR_C->SetBinContent(b, num_ourTauID);
      H_ourTauID_Data_CR_C->SetBinContent(b, den_ourTauID);
      H_TAUPOG_QCD_CR_C->SetBinContent(b, num_TAUPOG);
      H_TAUPOG_Data_CR_C->SetBinContent(b, den_TAUPOG);
    }
  }

  cout<<"ourTauID_QCD_CR_C "<< ourTauID_QCD_CR_C->Integral() << " nbins " << ourTauID_QCD_CR_C->GetXaxis()->GetNbins() << endl;
  cout<<"ourTauID_Data_CR_C "<< ourTauID_Data_CR_C->Integral() << " nbins " << ourTauID_Data_CR_C->GetXaxis()->GetNbins() << endl;

  cout<<"H_TAUPOG_QCD_CR_C "<< H_TAUPOG_QCD_CR_C->Integral() << " nbins " << H_TAUPOG_QCD_CR_C->GetXaxis()->GetNbins() << endl;
  cout<<"H_TAUPOG_Data_CR_C "<< H_TAUPOG_Data_CR_C->Integral() << " nbins " << H_TAUPOG_Data_CR_C->GetXaxis()->GetNbins() << endl;

  cout << " ni " << ni << " nf " << nf << endl;

  H_ourTauID_QCD_CR_C->GetXaxis()->SetRangeUser(ni, nf); 
  H_ourTauID_Data_CR_C->GetXaxis()->SetRangeUser(ni, nf); 

  H_TAUPOG_QCD_CR_C->GetXaxis()->SetRangeUser(ni, nf); 
  H_TAUPOG_Data_CR_C->GetXaxis()->SetRangeUser(ni, nf); 
  

  TH1F *H_ourTauID = (TH1F*)H_ourTauID_QCD_CR_C->Clone("h3");  
  H_ourTauID->Divide(H_ourTauID_Data_CR_C);

  TH1F *H_TAUPOG = (TH1F*)H_TAUPOG_QCD_CR_C->Clone("h3");  
  H_TAUPOG->Divide(H_TAUPOG_Data_CR_C);
  H_TAUPOG->Sumw2();
  H_TAUPOG->GetXaxis()->SetLimits(ni, nf); 


  H_ourTauID->Sumw2();
  H_ourTauID->GetXaxis()->SetLimits(ni, nf); 
  H_ourTauID->SetTitle("SS QCD purity ");
  H_ourTauID->GetYaxis()->SetTitle("(Data-nonQCD)/Data");
  H_ourTauID->GetYaxis()->SetTitleSize(0.04);
  H_ourTauID->GetYaxis()->SetRangeUser(0.4, 1.2); 
  H_ourTauID->GetXaxis()->SetTitleSize(0.04);
  H_ourTauID->GetXaxis()->SetTitle("m(#tau, #tau, #slash{E}_{T}) [GeV]");
  
  for (int b = 1; b <= H_ourTauID->GetXaxis()->GetNbins(); b++ ){
    cout << "b " << b << " mass interval " << ( H_ourTauID->GetXaxis()->GetBinLowEdge(b)) <<  "-" << (( H_ourTauID->GetXaxis()->GetBinLowEdge(b)) + (H_ourTauID->GetXaxis()->GetBinWidth(b)))  <<   " bc " << H_ourTauID->GetBinContent(b) << " Error " << H_ourTauID->GetBinError(b) <<  endl;
  }
  
  H_ourTauID->SetLineColor(4);
  H_ourTauID->SetLineWidth(3);
  H_ourTauID->Draw("HIST");

  H_TAUPOG->SetLineColor(2);
  H_TAUPOG->SetLineWidth(3);
  H_TAUPOG->Draw("HISTsame");

  TLegend *leg_massZprime = new TLegend(0.57, 0.68, 0.69, 0.88);

  //  leg_massZprime->SetHeader("Samples");
  //  c1->SetLegendFillColor(0);
  leg_massZprime->SetFillColor(0);
  leg_massZprime->SetBorderSize(1);
  leg_massZprime->SetTextSize(0.03);
  leg_massZprime->SetBorderSize(0);
  leg_massZprime->SetTextSize(0.025);
  leg_massZprime->AddEntry(H_ourTauID,"our TauID","L");
  leg_massZprime->AddEntry(H_TAUPOG,"TAUPOG TauID","L");

  leg_massZprime->Draw();


  //  H_ourTauID->Draw("L");
}

void setTDRStyle(){
  TStyle *tdrStyle = new TStyle("tdrStyle","Style for P-TDR");

  // For the canvas:
  tdrStyle->SetCanvasBorderMode(0);
  tdrStyle->SetCanvasColor(kWhite);
  tdrStyle->SetCanvasDefH(600); //Height of canvas
  tdrStyle->SetCanvasDefW(600); //Width of canvas
  tdrStyle->SetCanvasDefX(0);   //POsition on screen
  tdrStyle->SetCanvasDefY(0);
  // For the Pad:
  tdrStyle->SetPadBorderMode(0);
  // tdrStyle->SetPadBorderSize(Width_t size = 1);
  tdrStyle->SetPadColor(kWhite);
  tdrStyle->SetPadGridX(false);
  tdrStyle->SetPadGridY(false);
  tdrStyle->SetGridColor(0);
  tdrStyle->SetGridStyle(3);
  tdrStyle->SetGridWidth(1);
  // For the frame:
  tdrStyle->SetFrameBorderMode(0);
  tdrStyle->SetFrameBorderSize(1);
  tdrStyle->SetFrameFillColor(0);
  tdrStyle->SetFrameFillStyle(0);
  tdrStyle->SetFrameLineColor(1);
  tdrStyle->SetFrameLineStyle(1);
  tdrStyle->SetFrameLineWidth(1);

  // For the histo:
  tdrStyle->SetHistFillColor(0);
  // tdrStyle->SetHistFillStyle(0);
  tdrStyle->SetHistLineColor(1);
  tdrStyle->SetHistLineStyle(0);
  tdrStyle->SetHistLineWidth(1);
  // tdrStyle->SetLegoInnerR(Float_t rad = 0.5);
  // tdrStyle->SetNumberContours(Int_t number = 20);
//  tdrStyle->SetEndErrorSize(0);
  tdrStyle->SetErrorX(0.);
//  tdrStyle->SetErrorMarker(20);

  tdrStyle->SetMarkerStyle(20);

  //For the fit/function:
  tdrStyle->SetOptFit(1);
  tdrStyle->SetFitFormat("5.4g");
  //tdrStyle->SetFuncColor(1);
  tdrStyle->SetFuncStyle(1);
  tdrStyle->SetFuncWidth(1);

  //For the date:
  tdrStyle->SetOptDate(0);
  // tdrStyle->SetDateX(Float_t x = 0.01);
  // tdrStyle->SetDateY(Float_t y = 0.01);

  // For the statistics box:
  tdrStyle->SetOptFile(0);
  tdrStyle->SetOptStat("e"); // To display the mean and RMS:   SetOptStat("mr");
  //tdrStyle->SetStatColor(kWhite);
  tdrStyle->SetStatColor(kGray);
  tdrStyle->SetStatFont(42);

  tdrStyle->SetTextSize(11);
  tdrStyle->SetTextAlign(11);

  tdrStyle->SetStatTextColor(1);
  tdrStyle->SetStatFormat("6.4g");
  tdrStyle->SetStatBorderSize(0);
  tdrStyle->SetStatX(1.); //Starting position on X axis
  tdrStyle->SetStatY(1.); //Starting position on Y axis
  tdrStyle->SetStatFontSize(0.025); //Vertical Size
  tdrStyle->SetStatW(0.25); //Horizontal size 
  // tdrStyle->SetStatStyle(Style_t style = 1001);

  // Margins:
  tdrStyle->SetPadTopMargin(0.095);
  tdrStyle->SetPadBottomMargin(0.125);
  tdrStyle->SetPadLeftMargin(0.14);
  tdrStyle->SetPadRightMargin(0.1);

  // For the Global title:

  //  tdrStyle->SetOptTitle(0);
  tdrStyle->SetTitleFont(42);
  tdrStyle->SetTitleColor(1);
  tdrStyle->SetTitleTextColor(1);
  tdrStyle->SetTitleFillColor(10);
  tdrStyle->SetTitleFontSize(0.05);
  tdrStyle->SetTitleH(0.045); // Set the height of the title box
  //tdrStyle->SetTitleW(0); // Set the width of the title box
  tdrStyle->SetTitleX(0.15); // Set the position of the title box
  tdrStyle->SetTitleY(1.0); // Set the position of the title box
  // tdrStyle->SetTitleStyle(Style_t style = 1001);
  tdrStyle->SetTitleBorderSize(0);

  // For the axis titles:
  tdrStyle->SetTitleColor(1, "XYZ");
  tdrStyle->SetTitleFont(42, "XYZ");
  tdrStyle->SetTitleSize(0.06, "XYZ");
  // tdrStyle->SetTitleXSize(Float_t size = 0.02); // Another way to set the size?
  // tdrStyle->SetTitleYSize(Float_t size = 0.02);
  tdrStyle->SetTitleXOffset(0.9);
  tdrStyle->SetTitleYOffset(1.0);
  // tdrStyle->SetTitleOffset(1.1, "Y"); // Another way to set the Offset

  // For the axis labels:

  tdrStyle->SetLabelColor(1, "XYZ");
  tdrStyle->SetLabelFont(42, "XYZ");
  tdrStyle->SetLabelOffset(0.007, "XYZ");
  tdrStyle->SetLabelSize(0.03, "XYZ");

  // For the axis:

  tdrStyle->SetAxisColor(1, "XYZ");
  tdrStyle->SetStripDecimals(kTRUE);
  tdrStyle->SetTickLength(0.03, "XYZ");
  tdrStyle->SetNdivisions(510, "XYZ");
  tdrStyle->SetPadTickX(1);  // To get tick marks on the opposite side of the frame
  tdrStyle->SetPadTickY(1);

  // Change for log plots:
  tdrStyle->SetOptLogx(0);
  tdrStyle->SetOptLogy(0);
  tdrStyle->SetOptLogz(0);
  // Postscript options:
  // tdrStyle->SetPaperSize(15.,15.);
  // tdrStyle->SetLineScalePS(Float_t scale = 3);
  // tdrStyle->SetLineStyleString(Int_t i, const char* text);
  // tdrStyle->SetHeaderPS(const char* header);
  // tdrStyle->SetTitlePS(const char* pstitle);
  // tdrStyle->SetBarOffset(Float_t baroff = 0.5);
  // tdrStyle->SetBarWidth(Float_t barwidth = 0.5);
  // tdrStyle->SetPaintTextFormat(const char* format = "g");
  // tdrStyle->SetPalette(Int_t ncolors = 0, Int_t* colors = 0);
  // tdrStyle->SetTimeOffset(Double_t toffset);
  // tdrStyle->SetHistMinimumZero(kTRUE);

  tdrStyle->cd();
}

