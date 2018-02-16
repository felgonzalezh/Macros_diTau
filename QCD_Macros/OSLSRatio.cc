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
void OSLSRatio(){
    

  int SIGNIFICANCE_ABOVE = 600.0;
  
     int nb = 2;
     float BINS[3] = {0.0, SIGNIFICANCE_ABOVE, 10000.0};  
     double BINNER[3] = {0.0, SIGNIFICANCE_ABOVE, 10000.0};  

  //-------------------------------CR_D_FILES------------------------------
  TFile *Data_CR_D= TFile::Open("CR_D/Data.root","READ");
  if (Data_CR_D== 0) {
    printf("Error: cannot open QCD \n");
    return;
    }

  TFile *QCD_CR_D = TFile::Open("CR_D/QCD.root","READ");
  if (QCD_CR_D == 0) {
    printf("Error: cannot open QCD \n");
    return;
    }

  TFile *DY_CR_D = TFile::Open("CR_D/DY+Jets.root","READ");
  if (DY_CR_D == 0) {
    printf("Error: cannot open DY \n");
    return;
    }

  TFile *VV_CR_D = TFile::Open("CR_D/VV.root","READ");
  if (VV_CR_D == 0) {
    printf("Error: cannot open DiBoson \n");
    return;
    }

  TFile *WJ_CR_D = TFile::Open("CR_D/W+Jets.root","READ");
  if (WJ_CR_D == 0) {
    printf("Error: cannot open WJets \n");
    return;
    }

  TFile *TT_CR_D = TFile::Open("CR_D/tbar{t}.root","READ");
  if (TT_CR_D == 0) {
    printf("Error: cannot open TTbar_CR_D \n");
    return;
    }

  
  /*
  int nb = 1;
  float BINS[2] = {0.0, SIGNIFICANCE_ABOVE};  
  double BINNER[2] = {0.0, SIGNIFICANCE_ABOVE};  
  */
  //-------------------------------CR_B_FILES------------------------------
  TFile *QCD_CR_B = TFile::Open("CR_B/QCD.root","READ");
  if (QCD_CR_B == 0) {
    printf("Error: cannot open QCD \n");
    return;
    }

  TFile *Data_CR_B = TFile::Open("CR_B/Data.root","READ");
  if (Data_CR_B == 0) {
    printf("Error: cannot open DY \n");
    return;
    }

  TFile *DY_CR_B = TFile::Open("CR_B/DY+Jets.root","READ");
  if (DY_CR_B == 0) {
    printf("Error: cannot open DY \n");
    return;
    }

  TFile *VV_CR_B = TFile::Open("CR_B/VV.root","READ");
  if (VV_CR_B == 0) {
    printf("Error: cannot open DiBoson \n");
    return;
    }

  TFile *WJ_CR_B = TFile::Open("CR_B/W+Jets.root","READ");
  if (WJ_CR_B == 0) {
    printf("Error: cannot open WJets \n");
    return;
    }

  TFile *TT_CR_B = TFile::Open("CR_B/tbar{t}.root","READ");
  if (TT_CR_B == 0) {
    printf("Error: cannot open TTbar_CR_B \n");
    return;
    }

  // CR_D MASS HISTOGRAMS-UNBINNED
  TH1D *Mass_Data_CR_D = (TH1D*)Data_CR_D->Get("NDiTauCombinations/DiTauReconstructableMass");
  TH1D *Mass_QCD_CR_D = (TH1D*)QCD_CR_D->Get("NDiTauCombinations/DiTauReconstructableMass");
  TH1D *Mass_DY_CR_D = (TH1D*)DY_CR_D->Get("NDiTauCombinations/DiTauReconstructableMass");
  TH1D *Mass_DiBoson_CR_D = (TH1D*)VV_CR_D->Get("NDiTauCombinations/DiTauReconstructableMass");
  TH1D *Mass_WJets_CR_D = (TH1D*)WJ_CR_D->Get("NDiTauCombinations/DiTauReconstructableMass");
  TH1D *Mass_TTbar_CR_D = (TH1D*)TT_CR_D->Get("NDiTauCombinations/DiTauReconstructableMass");

  // CR_B MASS HISTOGRAMS-UNBINNED
  TH1D *Mass_Data_CR_B = (TH1D*)Data_CR_B->Get("NDiTauCombinations/DiTauReconstructableMass");
  TH1D *Mass_QCD_CR_B = (TH1D*)QCD_CR_B->Get("NDiTauCombinations/DiTauReconstructableMass");
  TH1D *Mass_DY_CR_B = (TH1D*)DY_CR_B->Get("NDiTauCombinations/DiTauReconstructableMass");
  TH1D *Mass_DiBoson_CR_B = (TH1D*)VV_CR_B->Get("NDiTauCombinations/DiTauReconstructableMass");
  TH1D *Mass_WJets_CR_B = (TH1D*)WJ_CR_B->Get("NDiTauCombinations/DiTauReconstructableMass");
  TH1D *Mass_TTbar_CR_B = (TH1D*)TT_CR_B->Get("NDiTauCombinations/DiTauReconstructableMass");

  // CR_B EVENT HISTOGRAMS-UNBINNED
  TH1D *Events_Data_CR_B = (TH1D*)Data_CR_B->Get("NDiTauCombinations/Events");
  TH1D *Events_QCD_CR_B = (TH1D*)QCD_CR_B->Get("NDiTauCombinations/Events");
  Events_QCD_CR_B->Sumw2();
  //  Events_QCD_CR_B->Scale(1.37);
  TH1D *Events_DY_CR_B = (TH1D*)DY_CR_B->Get("NDiTauCombinations/Events");
  TH1D *Events_WJets_CR_B = (TH1D*)WJ_CR_B->Get("NDiTauCombinations/Events");
  TH1D *Events_DiBoson_CR_B = (TH1D*)VV_CR_B->Get("NDiTauCombinations/Events");
  TH1D *Events_TTbar_CR_B = (TH1D*)TT_CR_B->Get("NDiTauCombinations/Events");

  // CR_B TOTAL NUMBER OF EVENT
  double N_Data_CR_B = Events_Data_CR_B->GetBinContent(2);
  double N_DY_CR_B = Events_DY_CR_B->GetBinContent(2);
  double N_QCD_CR_B = Events_QCD_CR_B->GetBinContent(2);
  double N_WJets_CR_B = Events_WJets_CR_B->GetBinContent(2);
  double N_DiBoson_CR_B = Events_DiBoson_CR_B->GetBinContent(2);
  double N_TTbar_CR_B = Events_TTbar_CR_B->GetBinContent(2);

  // CR_D EVENT HISTOGRAMS-UNBINNED
  TH1D *Events_Data_CR_D = (TH1D*)Data_CR_D->Get("NDiTauCombinations/Events");
  TH1D *Events_QCD_CR_D = (TH1D*)QCD_CR_D->Get("NDiTauCombinations/Events");
  Events_QCD_CR_D->Sumw2();
  //  Events_QCD_CR_D->Scale(1.37);
  TH1D *Events_DY_CR_D = (TH1D*)DY_CR_D->Get("NDiTauCombinations/Events");
  TH1D *Events_WJets_CR_D = (TH1D*)WJ_CR_D->Get("NDiTauCombinations/Events");
  TH1D *Events_DiBoson_CR_D = (TH1D*)VV_CR_D->Get("NDiTauCombinations/Events");
  TH1D *Events_TTbar_CR_D = (TH1D*)TT_CR_D->Get("NDiTauCombinations/Events");

  // CR_D TOTAL NUMBER OF EVENT
  double N_Data_CR_D = Events_Data_CR_D->GetBinContent(2);
  double N_DY_CR_D = Events_DY_CR_D->GetBinContent(2);
  double N_QCD_CR_D = Events_QCD_CR_D->GetBinContent(2);
  double N_WJets_CR_D = Events_WJets_CR_D->GetBinContent(2);
  double N_DiBoson_CR_D = Events_DiBoson_CR_D->GetBinContent(2);
  double N_TTbar_CR_D = Events_TTbar_CR_B->GetBinContent(2);


  // CR_B TOTAL ERROR OF EVENTS
  double N_error_Data_CR_B = Events_Data_CR_B->GetBinError(2);
  double N_error_DY_CR_B = Events_DY_CR_B->GetBinError(2);
  double N_error_QCD_CR_B = Events_QCD_CR_B->GetBinError(2);
  double N_error_WJets_CR_B = Events_WJets_CR_B->GetBinError(2);
  double N_error_DiBoson_CR_B = Events_DiBoson_CR_B->GetBinError(2);

  double N_error_TTbar_CR_B = Events_TTbar_CR_B->GetBinError(2);

  // BKG TOTAL EVENTS ERROR
  TH1D *N_TOTAL_CR_B = (TH1D*)Events_DY_CR_B->Clone("total");
  //  N_TOTAL_CR_B->Sumw2();
  N_TOTAL_CR_B->Add(Events_WJets_CR_B);
  N_TOTAL_CR_B->Add(Events_DiBoson_CR_B);
  N_TOTAL_CR_B->Add(Events_TTbar_CR_B);
  //  N_TOTAL_CR_B->Add(Events_QCD_CR_B);
  double totalbkg_CR_B = N_TOTAL_CR_B->GetBinContent(2);
  double totalerror_CR_B = N_TOTAL_CR_B->GetBinError(2);

  // CR_B TOTAL ERROR OF EVENTS
  double N_error_Data_CR_B = Events_Data_CR_B->GetBinError(2);
  double N_error_DY_CR_B = Events_DY_CR_B->GetBinError(2);
  double N_error_QCD_CR_B = Events_QCD_CR_B->GetBinError(2);
  double N_error_WJets_CR_B = Events_WJets_CR_B->GetBinError(2);
  double N_error_DiBoson_CR_B = Events_DiBoson_CR_B->GetBinError(2);
  double N_error_TTbar_CR_B = Events_TTbar_CR_B->GetBinError(2);

  // BKG TOTAL EVENTS ERROR
  TH1D *N_TOTAL_CR_D = (TH1D*)Events_DY_CR_D->Clone("total");
  //  N_TOTAL_CR_D->Sumw2();
  N_TOTAL_CR_D->Add(Events_WJets_CR_D);
  N_TOTAL_CR_D->Add(Events_DiBoson_CR_D);
  N_TOTAL_CR_D->Add(Events_TTbar_CR_D);
  //  N_TOTAL_CR_D->Add(Events_QCD_CR_D);
  double totalbkg_CR_D = N_TOTAL_CR_D->GetBinContent(2);
  double totalerror_CR_D = N_TOTAL_CR_D->GetBinError(2);

  // CR_D TOTAL ERROR OF EVENTS
  double N_error_Data_CR_D = Events_Data_CR_D->GetBinError(2);
  double N_error_DY_CR_D = Events_DY_CR_D->GetBinError(2);
  double N_error_QCD_CR_D = Events_QCD_CR_D->GetBinError(2);
  double N_error_WJets_CR_D = Events_WJets_CR_D->GetBinError(2);
  double N_error_DiBoson_CR_D = Events_DiBoson_CR_D->GetBinError(2);
  double N_error_TTbar_CR_D = Events_TTbar_CR_D->GetBinError(2);


  double OSLSratio = N_QCD_CR_B/N_QCD_CR_D;
  double B_R = N_error_QCD_CR_B/N_QCD_CR_B;
  double D_R = N_error_QCD_CR_D/N_QCD_CR_D;
  double B_R2 = B_R*B_R;
  double D_R2 = D_R*D_R;
  double uncOSLSratio = OSLSratio*sqrt(B_R2+D_R2);
  //  double uncPerTauleg = uncTauID/(2*sqrt(TauID));

  cout << " ********************************CR B******* " << endl;

  cout << " ********************************CR B******* " << endl;
  cout << " \\begin{tiny} " << endl;
  cout << " \\begin{table} " << endl;
  cout << " \\centering{ " << endl;
  cout << " \\begin{tabular}{ | l | r |} \\hline \\hline " << endl;
  cout << " \\multicolumn{1}{|c|}{\\textcolor{red}{CR_B YIELDS} } \\\\ \\hline \\hline " << endl;
  cout << setprecision(2) << std::fixed << " \\textbf{Data}         & \\textbf{" << N_Data_CR_B      << "}  $\\pm$  \\textbf{ " <<  setprecision(2) <<    N_error_Data_CR_B        << "    & \\textbf{" << N_Data_CR_D      << "}  $\\pm$  \\textbf{ " <<  setprecision(2) <<    N_error_Data_CR_D   << "} \\\\ \\hline " << endl;
  cout << setprecision(2) << std::fixed << " DY         & " << N_DY_CR_B      << "   $\\pm$   " <<  setprecision(2) <<    N_error_DY_CR_B        << "  & " << N_DY_CR_D      << "   $\\pm$   " <<  setprecision(2) <<    N_error_DY_CR_D      << " \\\\ \\hline " << endl;
  cout << setprecision(2) << std::fixed << " WJets      & " << N_WJets_CR_B   << "   $\\pm$   " <<  setprecision(2) <<    N_error_WJets_CR_B     << "  & " << N_WJets_CR_D      << "   $\\pm$   " <<  setprecision(2) <<    N_error_WJets_CR_D      << " \\\\ \\hline " << endl;
  cout << setprecision(2) << std::fixed << " DiBoson    & " << N_DiBoson_CR_B << "   $\\pm$   " <<  setprecision(2) <<    N_error_DiBoson_CR_B   << "  & " << N_DiBoson_CR_D      << "   $\\pm$   " <<  setprecision(2) <<    N_error_DiBoson_CR_D      << " \\\\ \\hline " << endl;
  cout << setprecision(2) << std::fixed << " TTbar      & " << N_TTbar_CR_B   << "   $\\pm$   " <<  setprecision(2) <<    N_error_TTbar_CR_B     << "  & " << N_TTbar_CR_D      << "   $\\pm$   " <<  setprecision(2) <<    N_error_TTbar_CR_D      << " \\\\ \\hline " << endl; 
  cout << setprecision(2) << std::fixed << " \\textbf{ TOTAL BKG } & \\textbf{ " << totalbkg_CR_B  << "}   $\\pm$  \\textbf{ " <<  setprecision(2) <<    totalerror_CR_B   << "} \\\\ \\hline " << endl;
  cout << setprecision(2) << std::fixed << " Data - Bkg & " << N_QCD_CR_B     << "   $\\pm$   " <<  setprecision(2) <<    N_error_QCD_CR_B       << "  & " << N_QCD_CR_D      << "   $\\pm$   " <<  setprecision(2) <<    N_error_QCD_CR_D      << " \\\\ \\hline " << endl;

  cout << setprecision(2) << std::fixed << " \\textcolor{blue}{$R_{OSLS}$}         & \\textcolor{blue}{" << OSLSratio      << "}  $\\pm$  \\textcolor{blue}{ " <<  setprecision(2) <<    uncOSLSratio      << "} \\\\ \\hline " << endl;

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
