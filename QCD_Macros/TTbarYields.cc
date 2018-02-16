#include "TFile.h"
#include "TTree.h"

#include "TH1F.h"

#include "THStack.h"
#include "TLegend.h"
#include "TColor.h"
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
using namespace std;

void setTDRStyle();
void TTbarYields(){

  TCanvas* c1 = new TCanvas("c1","c1",200,200,800,700);

  gStyle->SetOptStat(0);
  /*      
  int nb = 7;
  float BINS[8] = {200.0, 225.0, 250.0, 300.0, 350.0, 450.0, 600.0, 900.0};  
  double BINNER[8] = {200.0, 225.0, 250.0, 300.0, 350.0, 450.0, 600.0, 900.0};  
  */
  int nb = 14;
  float BINS[15] = {0.0,200.0, 225.0, 250.0, 300.0, 350.0, 450.0, 600.0, 750.0, 900.0, 1200.0, 1500.0, 2000.0, 2500.0, 3000.0};  
  double BINNER[15] = {0.0,200.0, 225.0, 250.0, 300.0, 350.0, 450.0, 600.0, 750.0, 900.0, 1200.0, 1500.0, 2000.0, 2500.0, 3000.0};  

  cout << "working" << endl;

  TFile *f1 = TFile::Open("newDMF_newTightIso_LooseElectron_TightMuon/SR/tbar{t}.root","READ");
  if (f1 == 0) {
    printf("Error: cannot open DY+Jets \n");
    return;
    }
  TH1D *Mass_3000 = (TH1D*)f1->Get("NDiTauCombinations/DiTauReconstructableMass");

  TFile *f2 = TFile::Open("newDMF_newTightIso_LooseElectron_TightMuon_TAUPOG_NewTriggerSF/SR/tbar{t}.root","READ");
  if (f2 == 0) {
    printf("Error: cannot open DY+Jets \n");
    return;
    }
  TH1D *Mass_3000_Trigger = (TH1D*)f2->Get("NDiTauCombinations/DiTauReconstructableMass");

  TH1D *H_Mass_3000 = new TH1D("h_3000", "h_3000", nb, BINS);
  TH1D *H_Mass_3000_Trigger = new TH1D("h_3000", "h_3000", nb, BINS);

  cout << "i " << Mass_3000->GetXaxis()->GetNbins() << endl; 
  cout << "b " << H_Mass_3000->GetXaxis()->GetNbins() << endl; 
  Int_t nbins   = Mass_3000->GetXaxis()->GetNbins();


  for (int b = 1; b <= H_Mass_3000->GetXaxis()->GetNbins(); b++ ){
    double num_3000 = 0;
    double num_3000_width = 0;

    double num_3000_trigger = 0;
    double num_3000_width_trigger = 0;

    for (int i = 1; i <= nbins; i++ ){
      if(((( Mass_3000->GetXaxis()->GetBinLowEdge(i)) + (Mass_3000->GetXaxis()->GetBinWidth(i))) <= ((H_Mass_3000->GetXaxis()->GetBinLowEdge(b))+ (H_Mass_3000->GetXaxis()->GetBinWidth(b)))) && ((( Mass_3000->GetXaxis()->GetBinLowEdge(i))+ (Mass_3000->GetXaxis()->GetBinWidth(i))) > ((H_Mass_3000->GetXaxis()->GetBinLowEdge(b))))){
	
	num_3000 += Mass_3000->GetBinContent(i);
	num_3000_trigger += Mass_3000_Trigger->GetBinContent(i);
	
      }else if( ( Mass_3000->GetXaxis()->GetBinLowEdge(i)) >= (H_Mass_3000->GetXaxis()->GetBinLowEdge(nb)+ (H_Mass_3000->GetXaxis()->GetBinWidth(nb))) && b==nb){//---- ELSE ES SOLO PARA EL OVERFLOW... SI SE NO QUIERE OVERFLOW (QUITAR ESTE ELSE)
	num_3000 += Mass_3000->GetBinContent(i);
	num_3000_trigger += Mass_3000_Trigger->GetBinContent(i);


      }else if( ( Mass_3000->GetXaxis()->GetBinLowEdge(i)) < (H_Mass_3000->GetXaxis()->GetBinLowEdge(1)+ (H_Mass_3000->GetXaxis()->GetBinWidth(1))) && b==1){//---- ELSE ES SOLO PARA EL UNDERFLOW... SI SE NO QUIERE OVERFLOW (QUITAR ESTE ELSE)
	//	num_error_error += abs(error->GetBinError(i));
	num_3000 += Mass_3000->GetBinContent(i);
	num_3000_trigger += Mass_3000_Trigger->GetBinContent(i);

      }else{
	continue;
      }
      num_3000_width = num_3000 / (H_Mass_3000->GetXaxis()->GetBinWidth(b));
      num_3000_width_trigger = num_3000_trigger / (H_Mass_3000_Trigger->GetXaxis()->GetBinWidth(b));
      
      H_Mass_3000->SetBinContent(b, num_3000);
      H_Mass_3000_Trigger->SetBinContent(b, num_3000_trigger);
    }
  }

  double max3000=0,max3000_trigger=0,MAX=0; 
  max3000 = H_Mass_3000->GetMaximum();
  max3000_trigger = H_Mass_3000_Trigger->GetMaximum();

  cout << "max     3000 " << max3000 << endl;
  cout << "max 3000 Trigger " << max3000_trigger << endl;

  for(int b=1; b<15; b++){
    cout << BINS[b-1] << " pt " << BINS[b] << " no " << H_Mass_3000->GetBinContent(b) << " with " << H_Mass_3000_Trigger->GetBinContent(b) << endl;
  }


  if(max3000_trigger > max3000){MAX = max3000_trigger*1.05;}else{MAX = max3000*1.05;}
  H_Mass_3000->SetLineColor(4);
  H_Mass_3000->SetLineWidth(3);
  H_Mass_3000->SetLineStyle(2);

  H_Mass_3000_Trigger->SetLineColor(2);
  H_Mass_3000_Trigger->SetLineWidth(3);
  H_Mass_3000_Trigger->SetLineStyle(2);

  cout << "3000 normal (Events) " << Mass_3000->Integral() << endl;
  cout << "3000 binned (Events/GeV) " << H_Mass_3000->Integral() << endl;

  TPad *pad1 = new TPad("pad1", "pad1",0.0,0.3,1.0,1.0);

  pad1->Draw();
  pad1->cd();
  //  pad1->SetLogy();
  pad1->SetTickx();
  pad1->SetTicky();

  //--------------FIRSTPAD
  H_Mass_3000->SetTitle("Comparison no Trigger-Trigger on MC for ttbar");
  H_Mass_3000->GetYaxis()->SetTitle("Events");
  H_Mass_3000->GetXaxis()->SetTitle("m(#tau, #tau, #slash{E}_{T})");


  H_Mass_3000->Draw("");
  H_Mass_3000_Trigger->Draw("same");

  
  TLegend *leg_massZprime = new TLegend(0.15, 0.68, 0.35, 0.88);
  leg_massZprime->SetFillColor(0);
  leg_massZprime->SetBorderSize(1);
  leg_massZprime->SetTextSize(0.05);
  leg_massZprime->SetBorderSize(0);
  leg_massZprime->AddEntry(H_Mass_3000,"our Trigger Method ","L");
  leg_massZprime->AddEntry(H_Mass_3000_Trigger,"TAUPOG Trigger Method","L");

  leg_massZprime->Draw();


  c1->cd();   
  
   
  TPad *pad2 = new TPad("pad2", "pad2",0.0,0.0,1.0,0.3);
  pad2->Draw();
  pad2->cd();
  pad2->SetGridy();
  pad2->SetTickx();
  pad2->SetTicky();
  pad2->SetTopMargin(0.02077151);
  pad2->SetBottomMargin(0.1829871);

  TH1D *M3000 = (TH1D*)H_Mass_3000->Clone("notrigger");


  M3000->Divide(H_Mass_3000_Trigger);


  M3000->SetTitle("");
  M3000->GetYaxis()->SetTitle("#frac{no trigger}{Trigger}");
  M3000->GetXaxis()->SetTitle("m(#tau, #tau, #slash{E}_{T})");

  M3000->SetLineColor(4);
  M3000->SetLineWidth(3);
  M3000->SetLineStyle(2);
  //  H_Sig->SetMarkerStyle(21);

  M3000->Draw("");


  return;
}  

void setTDRStyle(){
  TStyle *tdrStyle = new TStyle("tdrStyle","Style for P-TDR");

  // For the canvas:
  tdrStyle->SetCanvasBorderMode(0);
  tdrStyle->SetCanvasColor(kWhite);
  //  tdrStyle->SetCanvasDefH(600); //Height of canvas
  //  tdrStyle->SetCanvasDefW(600); //Width of canvas
  //  tdrStyle->SetCanvasDefX(0);   //POsition on screen
  //  tdrStyle->SetCanvasDefY(0);
  // For the Pad:
  //  tdrStyle->SetPadBorderMode(0);
  // tdrStyle->SetPadBorderSize(Width_t size = 1);
  tdrStyle->SetPadColor(kWhite);
  //  tdrStyle->SetPadGridX(false);
  //  tdrStyle->SetPadGridY(false);
  tdrStyle->SetGridColor(0);
  //  tdrStyle->SetGridStyle(3);
  //  tdrStyle->SetGridWidth(1);
  // For the frame:
  //  tdrStyle->SetFrameBorderMode(0);
  //  tdrStyle->SetFrameBorderSize(1);
  tdrStyle->SetFrameFillColor(0);
  tdrStyle->SetFrameFillStyle(0);
  tdrStyle->SetFrameLineColor(1);
  tdrStyle->SetFrameLineStyle(1);
  //  tdrStyle->SetFrameLineWidth(1);

  // For the histo:
  //  tdrStyle->SetHistFillColor(0);
  // tdrStyle->SetHistFillStyle(0);
  tdrStyle->SetHistLineColor(1);
  tdrStyle->SetHistLineStyle(0);
  //  tdrStyle->SetHistLineWidth(1);
  // tdrStyle->SetLegoInnerR(Float_t rad = 0.5);
  // tdrStyle->SetNumberContours(Int_t number = 20);
//  tdrStyle->SetEndErrorSize(0);


//  tdrStyle->SetErrorX(0.);


//  tdrStyle->SetErrorMarker(20);

  tdrStyle->SetMarkerStyle(20);

  //For the fit/function:
  tdrStyle->SetOptFit(1);
  //  tdrStyle->SetFitFormat("5.4g");
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
  //  tdrStyle->SetStatFont(42);

  tdrStyle->SetTextSize(11);
  //  tdrStyle->SetTextAlign(11);

  tdrStyle->SetStatTextColor(1);
  tdrStyle->SetStatFormat("6.4g");
  //  tdrStyle->SetStatBorderSize(0);
  tdrStyle->SetStatX(1.); //Starting position on X axis
  tdrStyle->SetStatY(1.); //Starting position on Y axis
  //  tdrStyle->SetStatFontSize(0.025); //Vertical Size
  tdrStyle->SetStatW(0.25); //Horizontal size 
  // tdrStyle->SetStatStyle(Style_t style = 1001);

  // Margins:
  tdrStyle->SetPadTopMargin(0.095);
  tdrStyle->SetPadBottomMargin(0.125);
  tdrStyle->SetPadLeftMargin(0.14);
  tdrStyle->SetPadRightMargin(0.1);

  // For the Global title:

  //  tdrStyle->SetOptTitle(0);
  tdrStyle->SetTitleColor(1);
  tdrStyle->SetTitleTextColor(1);
  tdrStyle->SetTitleFillColor(10);
  //  tdrStyle->SetTitleFontSize(0.05);
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
  //  tdrStyle->SetTitleXOffset(0.9);
  //  tdrStyle->SetTitleYOffset(1.0);
  // tdrStyle->SetTitleOffset(1.1, "Y"); // Another way to set the Offset

  // For the axis labels:

  tdrStyle->SetLabelColor(1, "XYZ");
  //tdrStyle->SetLabelFont(42, "XYZ");
  tdrStyle->SetLabelOffset(0.007, "XYZ");
  //  tdrStyle->SetLabelSize(0.03, "XYZ");

  // For the axis:

  tdrStyle->SetAxisColor(1, "XYZ");
  tdrStyle->SetStripDecimals(kTRUE);
  //  tdrStyle->SetTickLength(0.03, "XYZ");
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
