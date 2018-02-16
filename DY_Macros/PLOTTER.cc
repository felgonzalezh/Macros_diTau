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
void PLOTTER(){

  TCanvas* c1 = new TCanvas("c1","c1",200,200,800,700);

  gStyle->SetOptStat(0);
  /*
  int nb = 10;
  float BINS[11] = {0.0, 10.0, 20.0, 30.0, 40.0, 50.0, 60.0, 70.0, 80.0, 90.0, 100.0};  
  double BINNER[11] =  {0.0, 10.0, 20.0, 30.0, 40.0, 50.0, 60.0, 70.0, 80.0, 90.0, 100.0};  
  */

  int nb = 8;
  float BINS[9] = {20.0, 30.0, 40.0, 50.0, 60.0, 70.0, 80.0, 90.0, 100.0};  
  double BINNER[9] =  {20.0, 30.0, 40.0, 50.0, 60.0, 70.0, 80.0, 90.0, 100.0};  

  Int_t cVV = 17561; // color index                                                                     
  TColor *colorVV = new TColor(cVV, 222.0/255.0,  90.0/255.0, 106.0/255.0 );
  Int_t cWJet = 17562; // color index                                                                 
  TColor *colorWJet = new TColor(cWJet, 100.0/255.0, 182.0/255.0, 232.0/255.0 );
  Int_t cTT = 17563; // color index                                                                     
  TColor *colorTT = new TColor(cTT, 155.0/255.0, 152.0/255.0, 204.0/255.0 );
  Int_t cQCD = 17564; // color index                                                                    
  TColor *colorQCD = new TColor(cQCD, 250.0/255.0, 202.0/255.0, 255.0/255.0);
  Int_t cDY = 17565; // color index                                                                     
  TColor *colorDY = new TColor(cDY, 248.0/255.0, 206.0/255.0, 104.0/255.0);
    
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

  // SR MASS HISTOGRAMS-UNBINNED
  TH1D *Mass_QCD_SR = (TH1D*)QCD_SR->Get("NDiTauCombinations/DiTauInvariantMass");
  Mass_QCD_SR->Sumw2();
  Mass_QCD_SR->Scale(1.34);
  TH1D *Mass_DY_SR = (TH1D*)DY_SR->Get("NDiTauCombinations/DiTauInvariantMass");
  TH1D *Mass_Data_SR = (TH1D*)Data_SR->Get("NDiTauCombinations/DiTauInvariantMass");
  TH1D *Mass_DiBoson_SR = (TH1D*)VV_SR->Get("NDiTauCombinations/DiTauInvariantMass");
  TH1D *Mass_WJ_SR = (TH1D*)WJ_SR->Get("NDiTauCombinations/DiTauInvariantMass");
  TH1D *Mass_TTbar_SR = (TH1D*)TT_SR->Get("NDiTauCombinations/DiTauInvariantMass");

  // SR EVENT HISTOGRAMS-UNBINNED
  TH1D *Events_QCD_SR = (TH1D*)QCD_SR->Get("NDiTauCombinations/Events");
  Events_QCD_SR->Sumw2();
  Events_QCD_SR->Scale(1.34);
  TH1D *Events_DY_SR = (TH1D*)DY_SR->Get("NDiTauCombinations/Events");
  TH1D *Events_Data_SR = (TH1D*)Data_SR->Get("NDiTauCombinations/Events");
  TH1D *Events_WJ_SR = (TH1D*)WJ_SR->Get("NDiTauCombinations/Events");
  TH1D *Events_DiBoson_SR = (TH1D*)VV_SR->Get("NDiTauCombinations/Events");
  TH1D *Events_TTbar_SR = (TH1D*)TT_SR->Get("NDiTauCombinations/Events");

  // TOTAL MASS ERROR 
  TH1D *error_SR = new TH1D("error_SR", "error_SR", Mass_DY_SR->GetXaxis()->GetNbins(), Mass_DY_SR->GetXaxis()->GetXmin(), Mass_DY_SR->GetXaxis()->GetXmax() );
  //error_SR->Sumw2();
  error_SR->Add(Mass_DiBoson_SR);
  error_SR->Add(Mass_TTbar_SR);
  error_SR->Add(Mass_WJ_SR);
  error_SR->Add(Mass_DY_SR);
  error_SR->Add(Mass_QCD_SR);

  TH1D *H_error_SR = new TH1D("h_error_SR", "h_error_SR", nb, BINS);
  TH1D *H_Mass_Data_SR = new TH1D("h_Data_SR", "h_Data_SR", nb, BINS);
  TH1D *H_Mass_DY_SR = new TH1D("h_DY_SR", "h_DY_SR", nb, BINS);
  TH1D *H_Mass_QCD_SR = new TH1D("h_QCD_SR", "h_QCD_SR", nb, BINS);
  TH1D *H_Mass_WJ_SR = new TH1D("h_WJ_SR", "h_WJ_SR", nb, BINS);
  TH1D *H_Mass_TTbar_SR = new TH1D("h_TTbar_SR", "h_TTbar_SR", nb, BINS);
  TH1D *H_Mass_DiBoson_SR = new TH1D("h_DiBoson_SR", "h_DiBoson_SR", nb, BINS);

  H_error_SR = (TH1D*)error_SR->Rebin(nb, "error_SR_rebin", BINNER);
  H_Mass_Data_SR = (TH1D*)Mass_Data_SR->Rebin(nb, "Data_SR_rebin", BINNER);
  H_Mass_DY_SR = (TH1D*)Mass_DY_SR->Rebin(nb, "DY_SR_rebin", BINNER);
  H_Mass_QCD_SR = (TH1D*)Mass_QCD_SR->Rebin(nb, "QCD_SR_rebin", BINNER);
  H_WJ_SR = (TH1D*)Mass_WJ_SR->Rebin(nb, "WJ_SR_rebin", BINNER);
  H_Mass_TTbar_SR = (TH1D*)Mass_TTbar_SR->Rebin(nb, "TTbar_SR_rebin", BINNER);
  H_Mass_DiBoson_SR = (TH1D*)Mass_DiBoson_SR->Rebin(nb, "DiBoson_SR_rebin", BINNER);

  H_error_SR->Scale(0.1); 
  H_Mass_Data_SR->Scale(0.1); 
  H_Mass_DY_SR->Scale(0.1); 
  H_Mass_QCD_SR->Scale(0.1);
  H_WJ_SR->Scale(0.1);
  H_Mass_TTbar_SR->Scale(0.1);
  H_Mass_DiBoson_SR->Scale(0.1);


  int errorbins =  H_error_SR->GetXaxis()->GetNbins();
  Double_t* mcX = new Double_t[errorbins];
  Double_t* mcY = new Double_t[errorbins];
  Double_t* mcErrorX = new Double_t[errorbins];
  Double_t* mcErrorY = new Double_t[errorbins];
  
  for(int bin=0; bin < H_error_SR->GetXaxis()->GetNbins(); bin++) {
    mcY[bin] = H_error_SR->GetBinContent(bin+1);
    mcErrorY[bin] = H_error_SR->GetBinError(bin+1);
    mcX[bin] = H_error_SR->GetBinCenter(bin+1);
    mcErrorX[bin] = H_error_SR->GetBinWidth(bin+1) * 0.5;
  }
  
  TGraphErrors *mcError = new TGraphErrors(H_error_SR->GetXaxis()->GetNbins(),mcX,mcY,mcErrorX,mcErrorY);
  mcError->SetLineWidth(1);
  mcError->SetFillColor(1);
  mcError->SetFillStyle(3002);
  
  delete[] mcX;
  delete[] mcY;
  delete[] mcErrorX;
  delete[] mcErrorY;
  
  H_Mass_DY_SR->SetLineColor(1);
  H_Mass_DY_SR->SetFillColor(cDY);

  H_Mass_QCD_SR->SetLineColor(1);
  H_Mass_QCD_SR->SetFillColor(cQCD);

  H_Mass_DiBoson_SR->SetLineColor(1);
  H_Mass_DiBoson_SR->SetFillColor(cVV);

  H_Mass_WJ_SR->SetLineColor(1);
  H_Mass_WJ_SR->SetFillColor(cWJet);

  H_Mass_TTbar_SR->SetLineColor(1);
  H_Mass_TTbar_SR->SetFillColor(cTT);

  H_Mass_Data_SR->SetLineColor(1);
  H_Mass_Data_SR->SetMarkerStyle(20);
  //  H_Mass_3000->SetLineWidth(3);
  //  H_Mass_3000->SetLineStyle(2);

  TPad *pad1 = new TPad("pad1", "pad1",0.0,0.3,1.0,1.0);

  pad1->Draw();
  pad1->cd();
  //  pad1->SetLogy();
  pad1->SetTickx();
  pad1->SetTicky();
  
  //--------------FIRSTPAD
  THStack *hs = new THStack("hs","CMS Preliminary 35.9 fb^{-1} (13 TeV)");
  hs->Add(H_Mass_DiBoson_SR);
  hs->Add(H_Mass_TTbar_SR);
  hs->Add(H_Mass_WJ_SR);
  hs->Add(H_Mass_QCD_SR);
  hs->Add(H_Mass_DY_SR);

  
  THStack* hsdraw = hs;
  hsdraw->Draw("HIST");

  hsdraw->GetYaxis()->SetTitle("Events/GeV");
  //  hsdraw->GetXaxis()->SetTitle("m(#tau, #tau, #slash{E}_{T})");
  //  hsdraw->SetMaximum(1.07*hs->GetMaximum());
  hsdraw->SetMaximum(15);
  hsdraw->SetMinimum(0.0);
  //  hsdraw->GetBinError(3);

  TH1D *H_Sig = (TH1D*)H_Mass_Data_SR->Clone("sig");
  TH1D *BKG = (TH1D*)H_error_SR->Clone("bkg");
  //  TH1D *H_Sig = new TH1D("h_Sig", "h_Sig", nb, BINS);
  H_Sig->Sumw2();
  H_Sig->Divide(BKG);
  H_Sig->Sumw2();


  H_Mass_Data_SR->Draw("same");
  mcError->Draw("2");

  //  TLegend *leg_massZprime = new TLegend(0.12, 0.68, 0.24, 0.88);
  TLegend *leg_massZprime = new TLegend(0.15, 0.68, 0.35, 0.88);

  //  leg_massZprime->SetHeader("Samples");
  //  c1->SetLegendFillColor(0);
  leg_massZprime->SetFillColor(0);
  leg_massZprime->SetBorderSize(1);
  leg_massZprime->SetTextSize(0.025);
  leg_massZprime->SetBorderSize(0);
  leg_massZprime->SetTextSize(0.025);
  leg_massZprime->AddEntry(H_Mass_Data_SR,"Data ","P");
  leg_massZprime->AddEntry(H_Mass_TTbar_SR,"t#bar{t}","f");
  leg_massZprime->AddEntry(H_Mass_DiBoson_SR,"VV, H","f");
  leg_massZprime->AddEntry(H_Mass_QCD_SR,"QCD","f");
  leg_massZprime->AddEntry(H_Mass_WJ_SR,"W+Jets","f");
  leg_massZprime->AddEntry(H_Mass_DY_SR,"DY+Jets","f");


  leg_massZprime->Draw();

  c1->cd();   
  

  TPad *pad2 = new TPad("pad2", "pad2",0.0,0.0,1.0,0.3);
  pad2->Draw();
  pad2->cd();
  //  pad2->SetGridy();
  pad2->SetTickx();
  pad2->SetTicky();
  pad2->SetTopMargin(0.02077151);
  pad2->SetBottomMargin(0.1829871);


  double sig=0;
  double significance=0;
  double significance_error=0;
  for (int b = 1; b <= H_Mass_Data_SR->GetXaxis()->GetNbins(); b++ ){
    double s =0;
    double bkg =0;
    double s_error =0;
    double bkg_error =0;
    double dataR = 0;
    double mcR = 0;
    double dataR2 = 0;
    double mcR2 = 0;
    double uncTauID = 0;

    s=H_Mass_Data_SR->GetBinContent(b);
    bkg=BKG->GetBinContent(b);
    s_error=H_Mass_Data_SR->GetBinError(b);
    bkg_error=BKG->GetBinError(b);


    if(bkg == 0){
      sig=0;
    }else{
      sig=s/bkg;
      dataR = s_error/s;
      mcR = bkg_error/bkg;
      dataR2 = dataR*dataR;
      mcR2 = mcR*mcR;
      uncTauID = sig*sqrt(dataR2+mcR2);
    }

    
    H_Sig->SetBinContent(b,sig);
    H_Sig->SetBinError(b,uncTauID);
  }

  
  H_Sig->SetStats(0);      // No statistics on lower plot

  TH1D *H_ERROR = (TH1D*)H_Sig->Clone("DataMCR");

  int errorbins =  H_ERROR->GetXaxis()->GetNbins();
  Double_t* mcX = new Double_t[errorbins];
  Double_t* mcY = new Double_t[errorbins];
  Double_t* mcErrorX = new Double_t[errorbins];
  Double_t* mcErrorY = new Double_t[errorbins];
  
 for(int bin=0; bin < H_ERROR->GetXaxis()->GetNbins(); bin++) {                                                                                  
 
   mcY[bin] = (H_Sig->GetBinContent(bin)) ? 1.0 : H_ERROR->GetBinContent(bin+1);
   mcErrorY[bin] = (H_Sig->GetBinContent(bin)) ?  H_ERROR->GetBinError(bin+1)/H_ERROR->GetBinContent(bin+1) : H_ERROR->GetBinError(bin+1);
   mcX[bin] = H_ERROR->GetBinCenter(bin+1);
   mcErrorX[bin] = H_ERROR->GetBinWidth(bin+1) * 0.5;
   /*
   mcY[bin] = H_ERROR->GetBinContent(bin+1);                                                                                                                                        
    mcErrorY[bin] = H_ERROR->GetBinError(bin+1);                                                                                                                
    mcX[bin] = H_ERROR->GetBinCenter(bin+1);                                                                                                                                         
    mcErrorX[bin] = H_ERROR->GetBinWidth(bin+1) * 0.5;     */
  }                                                                                                                                                                                    
  

  TGraphErrors *mcError = new TGraphErrors(H_ERROR->GetXaxis()->GetNbins(),mcX,mcY,mcErrorX,mcErrorY);                                                                               
  mcError->SetLineWidth(1);                                          
  mcError->SetFillColor(1);
  mcError->SetFillStyle(3002); 
  delete[] mcX;                                                                                                  
  delete[] mcY;                                                                                                                    
  delete[] mcErrorX;                                                                                                                                                                 
  delete[] mcErrorY; 

  H_Sig->Sumw2();

  double ratiomax =0, ratiomin=0;
  ratiomax = H_Sig->GetMaximum();
  ratiomin = H_Sig->GetMinimum();
  H_Sig->SetMinimum(0.4);  // Define Y ..
  H_Sig->SetMaximum(1.4); // .. range

  H_Sig->GetYaxis()->SetTitleSize(0.09) ;
  H_Sig->GetYaxis()->SetLabelSize(0.07) ;
  H_Sig->GetYaxis()->SetTitleOffset(0.45);

  H_Sig->GetXaxis()->SetTitleSize(0.1) ;
  H_Sig->GetXaxis()->SetLabelSize(0.08) ;
  H_Sig->GetXaxis()->SetTitleOffset(0.7);

  //  H_Sig->SetTitleXFont(32,"t");
  H_Sig->SetTitle("");
  H_Sig->GetYaxis()->SetTitle("#frac{Data}{MC}");
  H_Sig->GetXaxis()->SetTitle("m(#tau_{1}, #tau_{2})");

  H_Sig->SetLineColor(1);
  H_Sig->SetMarkerStyle(20);

  TLine *line = new TLine(20,1,100,1);
  line->SetLineColor(kRed);
  line->SetLineStyle(2);


  H_Sig->Draw("P");    
  mcError->Draw("2");    
  line->Draw("L");


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
