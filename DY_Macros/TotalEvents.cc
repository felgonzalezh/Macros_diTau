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
void TotalEvents(){
    

  int SIGNIFICANCE_ABOVE = 600.0;
  
     int nb = 2;
     float BINS[3] = {0.0, SIGNIFICANCE_ABOVE, 10000.0};  
     double BINNER[3] = {0.0, SIGNIFICANCE_ABOVE, 10000.0};  

  //-------------------------------CR_C_FILES------------------------------
  TFile *Data_CR_C= TFile::Open("SS/Data.root","READ");
  if (Data_CR_C== 0) {
    printf("Error: cannot open QCD \n");
    return;
    }
  TH1D *Mass_Data_CR_C = (TH1D*)Data_CR_C->Get("NDiTauCombinations/DiTauInvariantMass");

  TFile *QCD_CR_C = TFile::Open("SS/QCD.root","READ");
  if (QCD_CR_C == 0) {
    printf("Error: cannot open QCD \n");
    return;
    }
  TH1D *Mass_QCD_CR_C = (TH1D*)QCD_CR_C->Get("NDiTauCombinations/DiTauInvariantMass");

  TFile *DY_CR_C = TFile::Open("SS/DY+Jets.root","READ");
  if (DY_CR_C == 0) {
    printf("Error: cannot open DY \n");
    return;
    }
  TH1D *Mass_DY_CR_C = (TH1D*)DY_CR_C->Get("NDiTauCombinations/DiTauInvariantMass");
  TFile *VV_CR_C = TFile::Open("SS/VV.root","READ");
  if (VV_CR_C == 0) {
    printf("Error: cannot open DiBoson \n");
    return;
    }
  TH1D *Mass_DiBoson_CR_C = (TH1D*)VV_CR_C->Get("NDiTauCombinations/DiTauInvariantMass");
  TFile *WJ_CR_C = TFile::Open("SS/W+Jets.root","READ");
  if (WJ_CR_C == 0) {
    printf("Error: cannot open WJets \n");
    return;
    }
  TH1D *Mass_WJets_CR_C = (TH1D*)WJ_CR_C->Get("NDiTauCombinations/DiTauInvariantMass");
  TFile *TT_CR_C = TFile::Open("SS/tbar{t}.root","READ");
  if (TT_CR_C == 0) {
    printf("Error: cannot open TTbar_CR_C \n");
    return;
    }
  TH1D *Mass_TTbar_CR_C = (TH1D*)TT_CR_C->Get("NDiTauCombinations/DiTauInvariantMass");
  
  /*
  int nb = 1;
  float BINS[2] = {0.0, SIGNIFICANCE_ABOVE};  
  double BINNER[2] = {0.0, SIGNIFICANCE_ABOVE};  
  */
  //-------------------------------SR_FILES------------------------------
  TFile *QCD_SR = TFile::Open("SS/QCD.root","READ");
  if (QCD_SR == 0) {
    printf("Error: cannot open QCD \n");
    return;
    }

  TFile *Data_SR = TFile::Open("DYCR/Data.root","READ");
  if (Data_SR == 0) {
    printf("Error: cannot open DY \n");
    return;
    }

  TFile *DY_SR = TFile::Open("DYCR/DY+Jets.root","READ");
  if (DY_SR == 0) {
    printf("Error: cannot open DY \n");
    return;
    }

  TFile *VV_SR = TFile::Open("DYCR/VV.root","READ");
  if (VV_SR == 0) {
    printf("Error: cannot open DiBoson \n");
    return;
    }

  TFile *WJ_SR = TFile::Open("DYCR/W+Jets.root","READ");
  if (WJ_SR == 0) {
    printf("Error: cannot open WJets \n");
    return;
    }

  TFile *TT_SR = TFile::Open("DYCR/tbar{t}.root","READ");
  if (TT_SR == 0) {
    printf("Error: cannot open TTbar_SR \n");
    return;
    }


  // SR EVENT HISTOGRAMS-UNBINNED
  TH1D *Events_Data_SR = (TH1D*)Data_SR->Get("NDiTauCombinations/Events");
  TH1D *Events_QCD_SR = (TH1D*)QCD_SR->Get("NDiTauCombinations/Events");
  Events_QCD_SR->Sumw2();
  Events_QCD_SR->Scale(1.34);
  TH1D *Events_DY_SR = (TH1D*)DY_SR->Get("NDiTauCombinations/Events");
  TH1D *Events_WJets_SR = (TH1D*)WJ_SR->Get("NDiTauCombinations/Events");
  TH1D *Events_DiBoson_SR = (TH1D*)VV_SR->Get("NDiTauCombinations/Events");
  TH1D *Events_TTbar_SR = (TH1D*)TT_SR->Get("NDiTauCombinations/Events");

  // SR TOTAL NUMBER OF EVENT
  double N_Data_SR = Events_Data_SR->GetBinContent(2);
  double N_DY_SR = Events_DY_SR->GetBinContent(2);
  double N_QCD_SR = Events_QCD_SR->GetBinContent(2);
  double N_WJets_SR = Events_WJets_SR->GetBinContent(2);
  double N_DiBoson_SR = Events_DiBoson_SR->GetBinContent(2);
  double N_TTbar_SR = Events_TTbar_SR->GetBinContent(2);

  // SR TOTAL ERROR OF EVENTS
  double N_error_Data_SR = Events_Data_SR->GetBinError(2);
  double N_error_DY_SR = Events_DY_SR->GetBinError(2);
  double N_error_QCD_SR = Events_QCD_SR->GetBinError(2);
  double N_error_WJets_SR = Events_WJets_SR->GetBinError(2);
  double N_error_DiBoson_SR = Events_DiBoson_SR->GetBinError(2);

  double N_error_TTbar_SR = Events_TTbar_SR->GetBinError(2);

  // BKG TOTAL EVENTS ERROR
  TH1D *N_TOTAL_SR = (TH1D*)Events_DY_SR->Clone("total");
  //  N_TOTAL_SR->Sumw2();
  N_TOTAL_SR->Add(Events_WJets_SR);
  N_TOTAL_SR->Add(Events_DiBoson_SR);
  N_TOTAL_SR->Add(Events_TTbar_SR);
  N_TOTAL_SR->Add(Events_QCD_SR);
  double totalbkg_SR = N_TOTAL_SR->GetBinContent(2);
  double totalerror_SR = N_TOTAL_SR->GetBinError(2);

  double TauID = N_Data_SR/totalbkg_SR;
  double dataR = N_error_Data_SR/N_Data_SR;
  double mcR = totalerror_SR/totalbkg_SR;
  double dataR2 = dataR*dataR;
  double mcR2 = mcR*mcR;
  double uncTauID = TauID*sqrt(dataR2+mcR2);
  double uncPerTauleg = uncTauID/(2*sqrt(TauID));

  cout << " *************************************** " << endl;
  cout << " \\begin{tiny} " << endl;
  cout << " \\begin{table} " << endl;
  cout << " \\centering{ " << endl;
  cout << " \\begin{tabular}{ | l | r |} \\hline \\hline " << endl;
  cout << " \\multicolumn{2}{|c|}{\\textcolor{red}{DY CR YIELDS} } \\\\ \\hline \\hline " << endl;
  cout << setprecision(2) << std::fixed << " \\textbf{Data}         & \\textbf{" << N_Data_SR      << "}  $\\pm$  \\textbf{ " <<  setprecision(2) <<    N_error_Data_SR      << "} \\\\ \\hline " << endl;
  cout << setprecision(2) << std::fixed << " DY         & " << N_DY_SR      << "   $\\pm$   " <<  setprecision(2) <<    N_error_DY_SR      << " \\\\ \\hline " << endl;
  cout << setprecision(2) << std::fixed << " WJets      & " << N_WJets_SR   << "   $\\pm$   " <<  setprecision(2) <<    N_error_WJets_SR   << " \\\\ \\hline " << endl;
  cout << setprecision(2) << std::fixed << " DiBoson    & " << N_DiBoson_SR << "   $\\pm$   " <<  setprecision(2) <<    N_error_DiBoson_SR << " \\\\ \\hline " << endl;
  cout << setprecision(2) << std::fixed << " TTbar      & " << N_TTbar_SR   << "   $\\pm$   " <<  setprecision(2) <<    N_error_TTbar_SR   << " \\\\ \\hline " << endl;
  cout << setprecision(2) << std::fixed << " QCD        & " << N_QCD_SR     << "   $\\pm$   " <<  setprecision(2) <<    N_error_QCD_SR     << " \\\\ \\hline " << endl;
  cout << setprecision(2) << std::fixed << " \\textbf{ TOTAL BKG } & \\textbf{ " << totalbkg_SR  << "}   $\\pm$  \\textbf{ " <<  setprecision(2) <<    totalerror_SR      << "} \\\\ \\hline " << endl;
  cout << setprecision(2) << std::fixed << " \\textcolor{blue}{Data/MC}         & \\textcolor{blue}{" << TauID      << "}  $\\pm$  \\textcolor{blue}{ " <<  setprecision(2) <<    uncTauID      << "} \\\\ \\hline " << endl;
  cout << setprecision(2) << std::fixed << " \\textcolor{red}{\\textbf{SF per Tau leg}}         & \\textcolor{red}{\\textbf{" << sqrt(TauID)      << "}}  $\\pm$  \\textcolor{red}{\\textbf{ " <<  setprecision(2) <<    uncPerTauleg      << "}} \\\\ \\hline " << endl;
  cout << " \\end{tabular} " << endl;
  cout << " } " << endl;
  cout << " \\end{table} " << endl;
  cout << " \\end{tiny} " << endl;
  cout << " *************************************** " << endl;

  //  cout << " \\vspace{-0.4cm} " << endl;



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
