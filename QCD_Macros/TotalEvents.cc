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
  TFile *Data_CR_C= TFile::Open("CR_C/Data.root","READ");
  if (Data_CR_C== 0) {
    printf("Error: cannot open QCD \n");
    return;
    }
  TH1D *Mass_Data_CR_C = (TH1D*)Data_CR_C->Get("NDiTauCombinations/DiTauReconstructableMass");

  TFile *QCD_CR_C = TFile::Open("CR_C/QCD.root","READ");
  if (QCD_CR_C == 0) {
    printf("Error: cannot open QCD \n");
    return;
    }
  TH1D *Mass_QCD_CR_C = (TH1D*)QCD_CR_C->Get("NDiTauCombinations/DiTauReconstructableMass");

  TFile *DY_CR_C = TFile::Open("CR_C/DY+Jets.root","READ");
  if (DY_CR_C == 0) {
    printf("Error: cannot open DY \n");
    return;
    }
  TH1D *Mass_DY_CR_C = (TH1D*)DY_CR_C->Get("NDiTauCombinations/DiTauReconstructableMass");
  TFile *VV_CR_C = TFile::Open("CR_C/VV.root","READ");
  if (VV_CR_C == 0) {
    printf("Error: cannot open DiBoson \n");
    return;
    }
  TH1D *Mass_DiBoson_CR_C = (TH1D*)VV_CR_C->Get("NDiTauCombinations/DiTauReconstructableMass");
  TFile *WJ_CR_C = TFile::Open("CR_C/W+Jets.root","READ");
  if (WJ_CR_C == 0) {
    printf("Error: cannot open WJets \n");
    return;
    }
  TH1D *Mass_WJets_CR_C = (TH1D*)WJ_CR_C->Get("NDiTauCombinations/DiTauReconstructableMass");
  TFile *TT_CR_C = TFile::Open("CR_C/tbar{t}.root","READ");
  if (TT_CR_C == 0) {
    printf("Error: cannot open TTbar_CR_C \n");
    return;
    }
  TH1D *Mass_TTbar_CR_C = (TH1D*)TT_CR_C->Get("NDiTauCombinations/DiTauReconstructableMass");
  
  /*
  int nb = 1;
  float BINS[2] = {0.0, SIGNIFICANCE_ABOVE};  
  double BINNER[2] = {0.0, SIGNIFICANCE_ABOVE};  
  */
  //-------------------------------SR_FILES------------------------------
  TFile *QCD_SR = TFile::Open("CR_C/QCD.root","READ");
  if (QCD_SR == 0) {
    printf("Error: cannot open QCD \n");
    return;
    }


  TFile *DY_SR = TFile::Open("SR/DY+Jets.root","READ");
  if (DY_SR == 0) {
    printf("Error: cannot open DY \n");
    return;
    }

  TFile *VV_SR = TFile::Open("SR/VV.root","READ");
  if (VV_SR == 0) {
    printf("Error: cannot open DiBoson \n");
    return;
    }

  TFile *WJ_SR = TFile::Open("SR/W+Jets.root","READ");
  if (WJ_SR == 0) {
    printf("Error: cannot open WJets \n");
    return;
    }

  TFile *TT_SR = TFile::Open("SR/tbar{t}.root","READ");
  if (TT_SR == 0) {
    printf("Error: cannot open TTbar_SR \n");
    return;
    }

  TFile *f2 = TFile::Open("SR/Zprime3000.root","READ");
  if (f2 == 0) {
    printf("Error: cannot open Zprime3000 \n");
    return;
    }

  // SR MASS HISTOGRAMS-UNBINNED
  TH1D *Mass_QCD_SR = (TH1D*)QCD_SR->Get("NDiTauCombinations/DiTauReconstructableMass");
  Mass_QCD_SR->Sumw2();
  Mass_QCD_SR->Scale(1.34);
  TH1D *Mass_DY_SR = (TH1D*)DY_SR->Get("NDiTauCombinations/DiTauReconstructableMass");
  TH1D *Mass_DiBoson_SR = (TH1D*)VV_SR->Get("NDiTauCombinations/DiTauReconstructableMass");
  TH1D *Mass_WJets_SR = (TH1D*)WJ_SR->Get("NDiTauCombinations/DiTauReconstructableMass");
  TH1D *Mass_TTbar_SR = (TH1D*)TT_SR->Get("NDiTauCombinations/DiTauReconstructableMass");
  TH1D *Mass_3000 = (TH1D*)f2->Get("NDiTauCombinations/DiTauReconstructableMass");
  // SR EVENT HISTOGRAMS-UNBINNED
  TH1D *Events_3000 = (TH1D*)f2->Get("NDiTauCombinations/Events");
  TH1D *Events_QCD_SR = (TH1D*)QCD_SR->Get("NDiTauCombinations/Events");
  Events_QCD_SR->Sumw2();
  Events_QCD_SR->Scale(1.34);
  TH1D *Events_DY_SR = (TH1D*)DY_SR->Get("NDiTauCombinations/Events");
  TH1D *Events_WJets_SR = (TH1D*)WJ_SR->Get("NDiTauCombinations/Events");
  TH1D *Events_DiBoson_SR = (TH1D*)VV_SR->Get("NDiTauCombinations/Events");
  TH1D *Events_TTbar_SR = (TH1D*)TT_SR->Get("NDiTauCombinations/Events");

  // SR TOTAL NUMBER OF EVENTS
  double N_DY_SR = Events_DY_SR->GetBinContent(2);
  double N_QCD_SR = Events_QCD_SR->GetBinContent(2);
  double N_WJets_SR = Events_WJets_SR->GetBinContent(2);
  double N_DiBoson_SR = Events_DiBoson_SR->GetBinContent(2);
  double N_TTbar_SR = Events_TTbar_SR->GetBinContent(2);
  double N_3000 = Events_3000->GetBinContent(2);
  // SR TOTAL ERROR OF EVENTS
  double N_error_DY_SR = Events_DY_SR->GetBinError(2);
  double N_error_QCD_SR = Events_QCD_SR->GetBinError(2);
  double N_error_WJets_SR = Events_WJets_SR->GetBinError(2);
  double N_error_DiBoson_SR = Events_DiBoson_SR->GetBinError(2);

  double N_error_TTbar_SR = Events_TTbar_SR->GetBinError(2);
  double N_error_3000 = Events_3000->GetBinError(2);

  // BKG TOTAL EVENTS ERROR
  TH1D *N_TOTAL_SR = (TH1D*)Events_DY_SR->Clone("total");
  //  N_TOTAL_SR->Sumw2();
  N_TOTAL_SR->Add(Events_WJets_SR);
  N_TOTAL_SR->Add(Events_DiBoson_SR);
  N_TOTAL_SR->Add(Events_TTbar_SR);
  N_TOTAL_SR->Add(Events_QCD_SR);
  double totalbkg_SR = N_TOTAL_SR->GetBinContent(2);
  double totalerror_SR = N_TOTAL_SR->GetBinError(2);

  // TOTAL MASS ERROR 
  TH1D *error_SR = new TH1D("error_SR", "error_SR", Mass_DY_SR->GetXaxis()->GetNbins(), Mass_DY_SR->GetXaxis()->GetXmin(), Mass_DY_SR->GetXaxis()->GetXmax() );
  //error_SR->Sumw2();
  error_SR->Add(Mass_DiBoson_SR);
  error_SR->Add(Mass_TTbar_SR);
  error_SR->Add(Mass_WJets_SR);
  error_SR->Add(Mass_DY_SR);
  error_SR->Add(Mass_QCD_SR);

  //  H_error_SR->Sumw2();

  TH1D *error_CR_C = new TH1D("error_CR_C", "error_CR_C", Mass_DY_CR_C->GetXaxis()->GetNbins(), Mass_DY_CR_C->GetXaxis()->GetXmin(), Mass_DY_CR_C->GetXaxis()->GetXmax() );
  //error_CR_C->Sumw2();
  error_CR_C->Add(Mass_DiBoson_CR_C);
  error_CR_C->Add(Mass_TTbar_CR_C);
  error_CR_C->Add(Mass_WJets_CR_C);
  error_CR_C->Add(Mass_DY_CR_C);
  error_CR_C->Add(Mass_QCD_CR_C);
  

  TH1D *H_error_CR_C = new TH1D("h_error_CR_C", "h_error_CR_C", nb, BINS);
  H_error_CR_C = (TH1D*)error_CR_C->Rebin(nb, "error_CR_C_rebin", BINNER);

  TH1D *H_Mass_Data_CR_C = new TH1D("h_Data_CR_C", "h_Data_CR_C", nb, BINS);
  H_Mass_Data_CR_C = (TH1D*)Mass_Data_CR_C->Rebin(nb, "Data_CR_C_rebin", BINNER);
  TH1D *H_Mass_DY_CR_C = new TH1D("h_DY_CR_C", "h_DY_CR_C", nb, BINS);
  H_Mass_DY_CR_C = (TH1D*)Mass_DY_CR_C->Rebin(nb, "DY_CR_C_rebin", BINNER);
  TH1D *H_Mass_QCD_CR_C = new TH1D("h_QCD_CR_C", "h_QCD_CR_C", nb, BINS);
  H_Mass_QCD_CR_C = (TH1D*)Mass_QCD_CR_C->Rebin(nb, "QCD_CR_C_rebin", BINNER);
  TH1D *H_Mass_WJets_CR_C = new TH1D("h_WJets_CR_C", "h_WJets_CR_C", nb, BINS);
  H_Mass_WJets_CR_C = (TH1D*)Mass_WJets_CR_C->Rebin(nb, "WJets_CR_C_rebin", BINNER);
  TH1D *H_Mass_DiBoson_CR_C = new TH1D("h_DiBoson_CR_C", "h_DiBoson_CR_C", nb, BINS);
  H_Mass_DiBoson_CR_C = (TH1D*)Mass_DiBoson_CR_C->Rebin(nb, "DiBoson_CR_C_rebin", BINNER);
  TH1D *H_Mass_TTbar_CR_C = new TH1D("h_TTbar_CR_C", "h_TTbar_CR_C", nb, BINS);
  H_Mass_TTbar_CR_C = (TH1D*)Mass_TTbar_CR_C->Rebin(nb, "TTbar_CR_C_rebin", BINNER);

  TH1D *H_Mass_TOTAL_CR_C = (TH1D*)H_Mass_DY_CR_C->Clone("total_c");
  H_Mass_TOTAL_CR_C->Add(H_Mass_WJets_CR_C);
  H_Mass_TOTAL_CR_C->Add(H_Mass_DiBoson_CR_C);
  H_Mass_TOTAL_CR_C->Add(H_Mass_TTbar_CR_C);
  

  TH1D *H_error_SR = new TH1D("h_error_SR", "h_error_SR", nb, BINS);
  H_error_SR = (TH1D*)error_SR->Rebin(nb, "error_SR_rebin", BINNER);
  TH1D *H_Mass_DY_SR = new TH1D("h_DY_SR", "h_DY_SR", nb, BINS);
  H_Mass_DY_SR = (TH1D*)Mass_DY_SR->Rebin(nb, "DY_SR_rebin", BINNER);
  TH1D *H_Mass_QCD_SR = new TH1D("h_QCD_SR", "h_QCD_SR", nb, BINS);
  H_Mass_QCD_SR = (TH1D*)Mass_QCD_SR->Rebin(nb, "QCD_SR_rebin", BINNER);
  TH1D *H_Mass_3000 = new TH1D("h_3000", "h_3000", nb, BINS);
  H_Mass_3000 = (TH1D*)Mass_3000->Rebin(nb, "3000_rebin", BINNER);

  double norm_WJets = 0;
  double error_WJets = 0;
  double norm_error = 0;
  double error_error = 0;

  TH1D *SIG = (TH1D*)H_Mass_3000->Clone("sig");
  TH1D *BKG = (TH1D*)H_error_SR->Clone("sig");
  TH1D *H_Sig = new TH1D("h_Sig", "h_Sig", nb, BINS);

  double sig=0;
  double significance=0;
  double significance_error=0;
  for (int b = 1; b <= H_Mass_3000->GetXaxis()->GetNbins(); b++ ){
    double s =0;
    double bkg =0;
    double s_error =0;
    double bkg_error =0;
    s=SIG->GetBinContent(b);
    bkg=BKG->GetBinContent(b);
    s_error=SIG->GetBinError(b);
    bkg_error=BKG->GetBinError(b);
    cout << " s " << s <<  " bkg " << s_error << " s+b " <<bkg << " sqrt " << bkg_error << endl;
    sig=s/sqrt(s+bkg);
    double den = sqrt((s+bkg)*(s+bkg)*(s+bkg));
    double s1 = (s+2*bkg)/den;
    double s2 = s/den;

    cout << s_error*s_error/4 << "   " << bkg_error*bkg_error/4 << " den " << den <<  endl;
    cout << (s+2*bkg)/den << "  " << s/den << endl;

    significance_error= sqrt((s_error*s_error*s1*s1/4)+(bkg_error*bkg_error*s2*s2/4));
    H_Sig->SetBinContent(b,sig);
    H_Sig->SetBinError(b,significance_error);

    cout << "sig " << sig << " +- " << significance_error << endl;
  }

  cout << " *************************************** " << endl;
  cout << " \\begin{tiny} " << endl;
  cout << " \\begin{table} " << endl;
  cout << " \\centering{ " << endl;
  cout << " \\begin{tabular}{ | l | r |} \\hline \\hline " << endl;
  cout << " \\multicolumn{2}{|c|}{\\textcolor{red}{OVERALL YIELDS} } \\\\ \\hline \\hline " << endl;
  cout << setprecision(2) << std::fixed << " DY         & " << N_DY_SR      << "   $\\pm$   " <<  setprecision(2) <<    N_error_DY_SR      << " \\\\ \\hline " << endl;
  cout << setprecision(2) << std::fixed << " WJets      & " << N_WJets_SR   << "   $\\pm$   " <<  setprecision(2) <<    N_error_WJets_SR   << " \\\\ \\hline " << endl;
  cout << setprecision(2) << std::fixed << " DiBoson    & " << N_DiBoson_SR << "   $\\pm$   " <<  setprecision(2) <<    N_error_DiBoson_SR << " \\\\ \\hline " << endl;
  cout << setprecision(2) << std::fixed << " TTbar      & " << N_TTbar_SR   << "   $\\pm$   " <<  setprecision(2) <<    N_error_TTbar_SR   << " \\\\ \\hline " << endl;
  cout << setprecision(2) << std::fixed << " QCD        & " << N_QCD_SR     << "   $\\pm$   " <<  setprecision(2) <<    N_error_QCD_SR     << " \\\\ \\hline " << endl;
  cout << setprecision(2) << std::fixed << " TOTAL BKG  & " << totalbkg_SR  << "   $\\pm$   " <<  setprecision(2) <<    totalerror_SR      << " \\\\ \\hline " << endl;
  cout << setprecision(2) << std::fixed << " Z$'$3000   & " << N_3000       << "   $\\pm$   " <<  setprecision(2) <<    N_error_3000       << " \\\\ \\hline " << endl;
  cout << " \\end{tabular} " << endl;
  cout << " } " << endl;
  cout << " \\end{table} " << endl;
  cout << " \\vspace{-0.5cm} " << endl;
  //**********************************SIGNIFICANCE******************************************                                                                                            
  cout << " \\begin{table} " << endl;
  cout << " \\centering{ " << endl;
  cout << " \\begin{tabular}{ | l | r |} \\hline \\hline " << endl;
  cout << setprecision(0) << " \\multicolumn{2}{|c|}{\\textcolor{red}{YIELD  ABOVE  " << BINS[1] << " }} \\\\ \\hline \\hline " << endl;
  //  for(int b = 1; b<3;b++){
  //   if(b==2){
      cout << setprecision(2) << " $Data^{C}$            & " << H_Mass_Data_CR_C->GetBinContent(2)  << "   $\\pm$   " << setprecision(2) << H_Mass_Data_CR_C->GetBinError(2) << " \\\\ \\hline " << endl;
      cout << setprecision(2) << " $nonQCD^{C}$          & " << H_Mass_TOTAL_CR_C->GetBinContent(2) << "   $\\pm$   " << setprecision(2) << H_Mass_TOTAL_CR_C->GetBinError(2) << " \\\\ \\hline " << endl;
      cout << setprecision(2) << " $Data^{C}-nonQCD^{C}$ & " << H_Mass_QCD_CR_C->GetBinContent(2)   << "   $\\pm$   " << setprecision(2) << H_Mass_QCD_CR_C->GetBinError(2) << " \\\\ \\hline " << endl;
      cout << setprecision(2) << " QCD                   & " << H_Mass_QCD_SR->GetBinContent(2)     << "   $\\pm$   " << setprecision(2) << H_Mass_QCD_SR->GetBinError(2) << " \\\\ \\hline " << endl;
      cout << setprecision(2) << " DY                    & " << H_Mass_DY_SR->GetBinContent(2)      << "   $\\pm$   " << setprecision(2) << H_Mass_DY_SR->GetBinError(2) << " \\\\ \\hline " << endl;
      cout << setprecision(2) << " \\textcolor{red}{TOTAL BKG}   & \\textcolor{red}{" <<  H_error_SR->GetBinContent(2)  << "   $\\pm$   " << setprecision(2) <<  H_error_SR->GetBinError(2) << "} \\\\ \\hline " << endl;
      cout << setprecision(2) << " \\textcolor{blue}{Z$'$3000}   & \\textcolor{blue}{" << H_Mass_3000->GetBinContent(2)      << "   $\\pm$   " << setprecision(2) << H_Mass_3000->GetBinError(2) << "} \\\\ \\hline " << endl;
      cout << setprecision(2) << " \\textbf{\\textcolor{green}{SIGNIFICANCE}} & \\textcolor{green}{ " << H_Sig->GetBinContent(2) << "} \\\\ \\hline " << endl;
      //      cout << setprecision(2) << " \\textbf{\\textcolor{green}{SIGNIFICANCE}} & \\textcolor{green}{ " << H_Sig->GetBinContent(2) << " $\\pm$   " << setprecision(2) << H_Sig->GetBinError(2) << "} \\\\ \\hline " << endl;
      //    }
      //  }
  cout << " \\end{tabular} " << endl;
  cout << " } " << endl;
  cout << " \\end{table} " << endl;
  cout << " \\end{tiny} " << endl;
  cout << " *************************************** " << endl;



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
