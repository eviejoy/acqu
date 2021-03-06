// SVN info: $Id: TA2CentralApparatus.h 70 2011-10-19 13:34:30Z mushkar $
#ifndef __TA2CentralApparatus_h__
#define __TA2CentralApparatus_h__

// STD
#include <vector>
using std::vector;
#include <map>
using std::map;
using std::pair;
using std::make_pair;
#include <iostream>

// AcquRoot
#include "TA2Apparatus.h"
#include "TA2CylMwpc.h"
#include "TA2Math.h"
#include "TA2Particle.h"

class TA2CalArray;
class TA2TrackLine;
class TA2CentralTrack;
class TA2MwpcTrack;
class HitCluster_t;
class TA2Particle;

class TA2CentralApparatus : public TA2Apparatus {
public:
  Bool_t fWait;
  void Test(); // for test
  
// Parameters
protected:
  static const Int_t    kNullHit   = static_cast<Int_t>(ENullHit);
  static const Double_t kNullFloat = ENullFloat;
  Bool_t	 fUseTracksBestMwpc;
  Int_t		 fMaxTrack;	// Max tracks number
  Double_t	 fFactorTrackLengthNaI; // TEST option under test
  Double_t	 fMaxPhiMwpcNaI;
  Double_t	 fMaxPhiTrackPid;
  Double_t	 fMaxPhiPidNaI;
  Double_t	 fMaxPhiMwpcInterNaI;
  Double_t	 fMaxPhiMwpcInterPid;  
  Double_t	 fLimitsPsVertex[3];
  Double_t	 fLengthPid;// TODO Must be moved into TA2PlasticPID
  Int_t	 	 fNpointsDroopPid;// TODO Must be moved into TA2PlasticPID
  Double_t	*fLostCorrPosPid;// TODO Must be moved into TA2PlasticPID
  Double_t	*fLostCorrFacPid;// TODO Must be moved into TA2PlasticPID
  //
public:
  virtual const Int_t	 &GetMaxTrack() const { return fMaxTrack; }
  virtual const Double_t &GetFactorTrackLengthNaI() const { return fFactorTrackLengthNaI; }// TEST option under test

// Detectors
protected:
  TA2Detector		 *fPid;		// Pointer to PID
  Int_t			  fNhitsPid;
  Int_t			 *fHitsPid;
  TVector2		 *fPositionsPid;
  Int_t			 *fIhitsPidUsed;
  Bool_t		 *fIhitsPidNotUsed;
  Int_t			  fNhitsPidNotUsed;
  //
  TA2CylMwpc		     *fMwpc;	// Pointer to MWPC
  Int_t			      fNchambers;
  const Double_t	     *fRmwpc;
  const TA2MwpcTrack	     *fTracksMwpc;
  const map<Double_t,Int_t>  *fTracksTrueMwpc;
  const map<Double_t,Int_t>  *fTracksTrueCandidateMwpc;
  const map<Double_t,Int_t>  *fTracksCandidateMwpc;
  const Int_t		     *fNintersTrueMwpc;
  const Int_t		    **fIintersTrueMwpc;
  const Int_t		     *fNintersCandidateMwpc;
  const Int_t		    **fIintersCandidateMwpc;
  //
  TA2CalArray		 *fNaI;		// Pointer to NaI
  Int_t			  fNclNaI;
  HitCluster_t		**fClNaI;
  UInt_t		 *fIdClNaI;     // Indices of hit clusters
  TVector3		 *fPositionsNaI;
  Bool_t		 *fUsedClNaI;
public:
  virtual const TA2CalArray	*GetNaI() const { return fNaI; }
  virtual const TA2Detector	*GetPid() const { return fPid; }
  virtual const TA2CylMwpc	*GetMwpc() const { return fMwpc; }
  virtual const TVector2	*GetPositionsPid(const Int_t i) const { return fPositionsPid+i; }
  virtual const TVector3	*GetPositionsNaI(const Int_t i) const { return fPositionsNaI+i; }
  virtual void			 SetUsedClNaI(const Int_t i) { fUsedClNaI[i] = kTRUE; }
  virtual Bool_t		 IsUsedClNaI(const Int_t i) const { return fUsedClNaI[i]; }
  virtual void			 SetUsedHitPid(const Int_t i) { fIhitsPidUsed[i]++; }
  virtual Bool_t		 IsUsedHitPid(const Int_t i) const { return fIhitsPidUsed[i]; }
  virtual Double_t CalcEhitPid(const Int_t, const TVector3&, const TVector3&) const;
  virtual Double_t CalcEtrackMwpc(const Int_t, const Int_t) const;
  
// Tracks
protected:
  Int_t			  fNtracks;
  TA2CentralTrack	 *fTracks;
  Int_t			  fNchTracks;
  Int_t			 *fIchTracks;
  Int_t			  fNneTracks;
  Int_t			 *fIneTracks;
  // Tracks with 2 MWPC
  map<Double_t,pair<Int_t,Int_t> > fMapMwpcTrueTrackNaI;          // sorted array of all possible Mwpc true track & NaI cluster combinations
  map<Double_t,pair<Int_t,Int_t> > fMapMwpcTrueCandidateTrackNaI; // sorted array of all possible Mwpc true-candidate track & NaI cluster combinations
  map<Double_t,pair<Int_t,Int_t> > fMapMwpcCandidateTrackNaI;     // sorted array of all possible Mwpc candidate track & NaI cluster combinations
  // Tracks with 1 MWPC
  Int_t			  fNtracksSingleMwpc;	     // # of possible tracks with a single MWPC
  TA2CentralTrack	 *fTracksSingleMwpc;	     // array of all possible tracks with NaI claster & MWPC intersection & (Pid)
  map<Double_t,Int_t>	  fMapMwpcTrueInterNaI;      // sorted array of all possible MWPC true intersection & NaI cluster combinations
  map<Double_t,Int_t>	  fMapMwpcCandidateInterNaI; // sorted array of all possible MWPC candidate intersection & NaI cluster combinations
  Int_t			  fNtracksSingleMwpcBest;    // # of the best tracks with a single MWPC which added to the fTracks
  // Not used MWPC intersections
  Int_t			 *fNintersTrueMwpcNotUsed;	// not used true MWPC intersections
  Int_t			 *fNintersCandidateMwpcNotUsed;	// not used candidate MWPC intersections
  // For histograms
  Double_t	*fPhiMwpcTrackNaI; // [fNtracks]
  Double_t	*fPhiTrackPid; // [fNtracks]
  Double_t	*fPhiMwpcTrackPid; // [fNtracks]
  Double_t	*fPhiInterSingleMwpcNaI; // [fNtracksSingleMwpc]
  Double_t	*fPhiTrackSingleMwpcPid; // [fNtracksSingleMwpc]
  Double_t	*fPhiMwpcInterNaI; // [fNtracks]
  Double_t	*fPhiMwpcInterPid; // [fNtracks]
  Double_t	*fPhiPidNaI; // [fNtracks]
  Double_t	*fTrackType; // [fNtracks]
  Double_t	*fTrackTheta; // [fNtracks]
  Double_t	*fTrackPhi; // [fNtracks]
  Double_t	*fPsVertex[3];// [fNtracks]
  Double_t	*fPsVertexR; // [fNtracks]
  Double_t	*fEclNaI; // [fNtracks]
  Double_t	*fEhitPid; // [fNtracks]
  Double_t	*fEtrackMwpc; // [fNtracks]
  //
  virtual void	MakeTracks();
  virtual void	MakeTracksTrue(const map<Double_t,Int_t>*, map<Double_t,pair<Int_t,Int_t> >&);
  virtual void	MakeTracksPidMwpc(const map<Double_t,Int_t>*);
  virtual void	MakeTracksMwpc(const map<Double_t,Int_t>*);
  virtual void	MakeTracksTrue(const Int_t**, const Int_t*, map<Double_t,Int_t>&);
  virtual void	MakeTracksPidMwpc(const Int_t**, const Int_t*);
  virtual void	MakeTracksPidNaI();
  virtual void	CountNotUsedPid();
  virtual void	CountNotUsedIntersMwpc(const Int_t**,const Int_t*,Int_t*);
  virtual void	AddTrack(const Int_t, const Int_t, const Int_t, const Int_t, const TVector3&, const TVector3&, const TVector3&);
  virtual void	AddTrack(const TA2CentralTrack&);
  virtual Bool_t	TooManyTracks() const { return fNtracks >= fMaxTrack; }
  virtual Bool_t	TooManyTracksSingleMwpc() const { return fNtracksSingleMwpc>=fMaxTrack; }

public:
  virtual const Int_t	&GetNtracks() const { return fNtracks; }
  virtual const Int_t	*GetNtracksPtr() const { return &fNtracks; }
  virtual const TA2CentralTrack *GetTracks() const { return fTracks; }
  virtual const Int_t	&GetNch() const { return fNchTracks;}
  virtual const Int_t	*GetNchPtr() const { return &fNchTracks;}
  virtual const Int_t	*GetIchTracks() const { return fIchTracks; }
  virtual const Int_t	&GetNne() const { return fNneTracks; }
  virtual const Int_t	*GetNnePtr() const { return &fNneTracks; }
  virtual const Int_t	*GetIneTracks() const { return fIneTracks; }
  //
  virtual const Int_t	&GetNtracksSingleMwpc() const { return fNtracksSingleMwpc; }
  virtual const Int_t	*GetNtracksSingleMwpcPtr() const { return &fNtracksSingleMwpc; }
//   virtual const map<Double_t,Int_t> *GetMapTracksTrueSingleMwpc() const { return &fMapTracksTrueSingleMwpc; }
//   virtual const map<Double_t,Int_t> *GetMapTracksCandidateSingleMwpc() const { return &fMapTracksCandidateSingleMwpc; }
  virtual const Int_t	&GetNtracksSingleMwpcBest() const { return fNtracksSingleMwpcBest; }
  virtual const Int_t	*GetNtracksSingleMwpcBestPtr() const { return &fNtracksSingleMwpcBest; }

// Vertexes
protected:
  Int_t		 fNvertexes;
  TVector3	*fVertexes;
  Int_t	       **fIvertexes;
  // For the output hists
  Double_t	*fVert[3];	// vertex {x,y,z}
  Double_t	*fVertR;	// vertex R
  Double_t	*fTrackDist;	// distance between 2 tracks forming a given vertex
  //
  virtual void	 MakeVertexes();
public:
  const Int_t		&GetNvertexes() const { return fNvertexes; }
  const TVector3	*GetVertexes() const { return fVertexes; }

// Particles
protected:
  Int_t	 *fType;
  Int_t	 *fSize;
  Int_t	 *fDet;
  Int_t	 *fCentral;
  Double_t *fTime;
   
public:
  virtual void	 AddParticleInfo(const TA2CentralTrack&);
  TA2Particle* GetParticles() { return fParticleInfo; }
  TA2Particle GetParticles(Int_t index){ return fParticleInfo[index]; }

//
public:
  TA2CentralApparatus( const char*, TA2System* );  // pass ptr to analyser
  virtual ~TA2CentralApparatus();                  // destructor
  virtual void		  PostInit();                    // some setup after parms read in
  virtual TA2DataManager *CreateChild( const char*, Int_t );
  virtual void		  LoadVariable(  );              // display setup
  virtual void		  Reconstruct( );                // event by event analysis
  virtual void		  SetConfig( Char_t*, Int_t );   // setup decode in implement
  virtual void		  Cleanup();			// reset event
  virtual void		  DeleteArrays();		// flush local new store
  virtual void		  MarkEndBuffers();		// Mark EndBuffer for the output arrays
  
  ClassDef(TA2CentralApparatus,1) // Central detector tracks reconstruction (PID+MWPC+CB)
};

//_______________________________________________________________________________
inline Double_t TA2CentralApparatus::CalcEhitPid(const Int_t iHitPid, const TVector3 &orig, const TVector3 &dir) const
{
  // Returns corrected Pid energy
  // Make droop correction for light attenuation inside PID strips
  // Make particle path correction
  
  // Check if Pid there is a Pid hit
  if ( iHitPid == kNullHit ) return kNullFloat;
  
  // Droop factor
  Double_t factorDroop = 1.;
  
  //Droop correction
  if (fNpointsDroopPid)
  {
    Double_t lPath;
    // TODO calc correction in 3D space TODO Make correct comparision with a given precision
    if ( dir.Theta() == kPi/2. ) //If theta = 90 set light path length by hand
      lPath = fLengthPid/2.;
    else //Theta is not 90
      lPath = fLengthPid/2. - fPositionsPid[iHitPid].Mod()/TMath::Tan(dir.Theta()); //Calculate light path length
    
    // Find the position in correction factor array
    Int_t iPos;
    for (iPos=0; iPos<fNpointsDroopPid-1; ++iPos)
    {
      if ( lPath >= fLostCorrPosPid[iPos] && lPath <= fLostCorrPosPid[iPos+1] ) break;
    }
    factorDroop = (lPath - fLostCorrPosPid[iPos]) * (fLostCorrFacPid[iPos+1] - fLostCorrFacPid[iPos]) / (fLostCorrPosPid[iPos+1] - fLostCorrPosPid[iPos]) + fLostCorrFacPid[iPos];
  }
  
  // Geom correction factor TODO Calc correction taking into account x-y shift
  Double_t factorGeom = TMath::Sin(dir.Theta());
  
  return fPid->GetEnergy(fHitsPid[iHitPid]) * factorDroop * factorGeom;
}

//_______________________________________________________________________________
inline Double_t TA2CentralApparatus::CalcEtrackMwpc(const Int_t iInterMwpc0, const Int_t iInterMwpc1) const
{
  // Returns composite MWPC track energy
  
  if (iInterMwpc0 == kNullHit && iInterMwpc1 == kNullHit) return kNullFloat;
  
  Double_t e = 0.;
  if (iInterMwpc0 != kNullHit) e  = fMwpc->GetInters(0,iInterMwpc0)->GetAclIE();
  if (iInterMwpc1 != kNullHit) e += fMwpc->GetInters(1,iInterMwpc1)->GetAclIE();
  
  return e;
}

//_______________________________________________________________________________
inline void TA2CentralApparatus::MarkEndBuffers()
{
  // EndBuffers
  
  // ParticleInfo
  fType[fNparticle]    = EBufferEnd;
  fTime[fNparticle]    = EBufferEnd;
  fSize[fNparticle]    = EBufferEnd;
  fCentral[fNparticle] = EBufferEnd;
  fDet[fNparticle]     = EBufferEnd;
  
  //
  fTrackType[fNtracks]  = EBufferEnd;
  fTrackTheta[fNtracks] = EBufferEnd;
  fTrackPhi[fNtracks]   = EBufferEnd;
  fEclNaI[fNtracks]     = EBufferEnd;
  fEhitPid[fNtracks]    = EBufferEnd;
  fEtrackMwpc[fNtracks] = EBufferEnd;
  for (Int_t i=0; i<3; ++i)
  {
    fPsVertex[i][fNtracks] = EBufferEnd;
  }
  fPsVertexR[fNtracks] = EBufferEnd;
  
  // Vertexes
  for (Int_t i=0; i<3; ++i)
  {
    fVert[i][fNvertexes] = EBufferEnd;
  }
  fVertR[fNvertexes] = EBufferEnd;
  fTrackDist[fNvertexes] = EBufferEnd;
}

      // //_________________________________________________________________________________
      // inline Double_t TA2CentralApparatus::GetCBMeanTime()
      // {
	//   Double_t time = 0.0;
	//   Int_t counter = 0;
	//   UInt_t* id_clCal = fNaI->GetClustHit();    //Indices of hit clusters
	//   HitCluster_t** clCal = fNaI->GetCluster(); //Pointer to cluster structs
	//   HitCluster_t* cl;                          //Cluster struct
	// 
	//   for(Int_t i = 0; i<fNparticle; i++)
	//   {
	  //     if(fPDG_ID[i]==kGamma)
	  //     {
	    //      cl = clCal[id_clCal[i]];
	    //      time = time + cl->GetTime();
	    //      counter++;
	    //     }
	    //   }
	    //   if(counter==0)
	    //     return 0.0;
	    //   else
	    //     return (time/counter);
	    // }
	    

#endif
