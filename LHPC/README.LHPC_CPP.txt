/*****************************************************************************\
 * README.LHPC_CPP.txt                                                       *
 *                                                                           *
 *  Created on: Jan 27, 2012                                                 *
 *      Author: Ben O'Leary (benjamin.oleary@gmail.com)                      *
 *      Copyright 2012 Ben O'Leary                                           *
 *                                                                           *
 *      This file is part of LesHouchesParserClasses (LHPC).                 *
 *                                                                           *
 *      LesHouchesParserClasses is free software: you can redistribute it    *
 *      and/or modify it under the terms of the GNU General Public License   *
 *      as published by the Free Software Foundation, either version 3 of    *
 *      the License, or (at your option) any later version.                  *
 *                                                                           *
 *      LesHouchesParserClasses is distributed in the hope that it will be   *
 *      useful, but WITHOUT ANY WARRANTY; without even the implied warranty  *
 *      of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU *
 *      General Public License for more details.                             *
 *                                                                           *
 *      You should have received a copy of the GNU General Public License    *
 *      (in LHPC/GNU_public_license.txt ) along with                         *
 *      LesHouchesParserClasses.  If not, see                                *
 *      <http://www.gnu.org/licenses/>.                                      *
 *      A full list of the files of LesHouchesParserClasses is at the end of *
 *      this file.                                                           *
\*****************************************************************************/

 Now that the legalese preamble is out of the way, the description of the code
 and how to use it can begin!

 LesHouchesParserClasses (LHPC) is a set of classes for interpreting files in
 the Les Houches Event File (LHEF) format and SUSY Les Houches Accord (SLHA)
 format. It also parses Flavor Les Houches Accord (FLHA) files, though with
 less functionality. This set of files is the version written in C++.

 There are 3 main parts to LHPC: the LHCO parser and associated structures; the
 LHEF parser and associated structures; and the SLHA parser and associated
 structures.
 
 There is also code to automatically plot SLHA spectra using the SLHA parser,
 though this requires the use of external programs: gnuplot, latex, dvips, and
 ps2eps (or ps2epsi).

 Running make on the makefile included will compile the library
 (LHPC/lib/libLHPC.a) and 4 executables (LHPC/bin/LhpcSpectrumPlotter.exe,
 LHPC/bin/LhefParserExample.exe, LHPC/bin/LhcoParserExample.exe, and
 LHPC/bin/SlhaParserExample.exe). The executables can be run with test input
 files in the LHPC/bin/testing directory.



** SLHA spectrum plotter
 As mentioned above, running make will produce LhpcSpectrumPlotter.exe, which
 can be run without any arguments to show further information on how to use it.
 Please ensure that the paths in the control block are correct! The paths in
 the examples in LHPC/bin/testing use the paths that seem to me to be the
 'standard' Linux paths.



 * C++ library code
 
 I have written LhcoParserExample.cpp, LhefParserExample.cpp and
 SlhaParserExample.cpp as examples for how to use the codes. I hope that they
 are commented well enough to be understandable. Some basic knowledge of C++
 (such as knowing what templates are) is required.


** LHPC::LhcoParser
   - this class is for reading in events from a file in the LHCO format.
   
 The essential functionality of this class is already covered by MadAnalysis 5.
 The LhcoParser class was written independently of MadAnalysis, and provides
 the functionality of reading LHCO files directly into C++ code.
 
 The intended use of LhcoParser is that an instance of the class is constructed
 with the name of the LHCO-format file that it should open, then
  readNextEvent() is called for as long as necessary. The readNextEvent()
 function returns false when the file can no longer be read, which in normal
 circumstances is when the end of the file has been reached.
 
 The LhcoParser holds a single event at a time, as a LHPC::LHCO::LhcoEvent,
 which holds the information from the 1st line of the event directly and the
 objects information as a set of LHPC::LHCO::ObjectLine instances, which each
 hold the information of a single line describing an object and its momentum
 from the event.

 One can read LhcoEvent.hpp and ObjectLine.hpp for the full information on
 these classes, but I expect that, for an example LhcoEvent called
 exampleEvent, exampleEvent.getObjectsOfType( int const whichType ) to get
 std::list< ObjectLine const* >s of all the objects of a given type in the
 event, and exampleEvent[ whichLine ] to get the line number whichLine (the
 first line is 1, not 0) would be the most used functions. I expect that, for
 each example ObjectLine called exampleLine,
 exampleLine.getTransverseMomentum() and the other named functions, or
 equivalently exampleLine[ whichEntry ], to get the whichEntry-th number of the
 line (starting with 0 for the object number, followed by its type at [ 1 ],
 pseudorapidity at [ 2 ] and so on) would be the most-used functions.
 


** LHPC::LhefParser
   - this class is for reading in events from a file in the LHEF format.
   
 The essential functionality of this class is already covered by the classes in
 the LesHouches directory of an installation of the publicly-available code
 ThePEG (typically part of an installation of Herwig++). The LhefParser class
 was written independently of the code in ThePEG, and provides an extra layer
 of interpretation beyond just filling the HEPRUP and HEPEUP groupings of the
 old Les Houches Accord format.
 
 The intended use of LhefParser is that an instance of the class is constructed
 with the name of the LHEF-format file that it should open, then
 readNextEvent() is called for as long as necessary. The readNextEvent()
 function returns false when the file can no longer be read, which in normal
 circumstances is when the end of the file has been reached, though reading
 stops as soon as an event is found which is not in the valid format, either by
 invalid XML, or by having the wrong number of data entries on any line, or by
 disagreement between the number of lines describing particles given in the 1st
 line of the event and the actual number of lines describing particles between
 "<event>" and "</event>".
 
 At this basic level, the LhefParser holds a single event at a time, as a
 LHPC::LHEF::LhefEvent, which holds the HEPRUP information (the information
 from the 1st line of the event) directly and the HEPEUP information as a set
 of LHPC::LHEF::ParticleLine instances, which each hold the information of a
 single line describing a particle and its momentum from the event.
 
 One can read LhefEvent.hpp and ParticleLine.hpp for the full information on
 these classes, but I expect that, for an example LhefEvent called
 exampleEvent, exampleEvent.getEventWeight() (or exampleEvent.XWGTUP()
 equivalently) to get the event's weight, exampleEvent.getNumberOfParticles()
 (or exampleEvent.NUP() equivalently) to get the number of particle lines of
 the event, and exampleEvent[ whichLine ] (or exampleEvent.getLine( whichLine )
 equivalently) to get the line number whichLine (the first line is 1, not 0)
 would be the most used functions. I expect that, for each example
 ParticleLine called exampleLine,
 exampleLine.getXMomentum()/.getYMomentum()/.getZMomentum()/.getEnergy(), or
 equivalently exampleLine.IPUP( 1 )/.IPUP( 2 )/.IPUP( 3 )/.IPUP( 4 ), to get
 the particle's momentum, and exampleLine.getPrimaryMotherLineNumber, or
 equivalently exampleLine.MOTHUP( 1 ), to get the primary mother particle line
 number to find the source of this particle would be the most-used functions.
 
 The further functionality mentioned above is pretty much two aspects: the
 minor convenience of the ParticleLines having direct pointers to their
 mother and daughter lines, and automatic collection of ParticleLine subsets of
 the event prepared by the LHPC::LHEF::AutomaticEventFilter class. The intended
 use of this class is as an aid to analyze an event (e.g. for whether to accept
 it or reject it): each time a new event is read in, each AutomaticEventFilter
 instance makes a std::list< LHPC::LHEF::ParticleLine const* > of pointers to
 the ParticleLines which pass its own FilterRule criteria (note that this does
 not _remove_ any lines from the LhefEvent, the list is prepared in addition).
 This could be used for example by setting up a filter to collect all the lines
 corresponding to final-state muons or antimuons with transverse momentum
 greater than e.g. 10 GeV, and then one can quickly find how many of these
 occur in the last read event by asking for the size of the list that the
 filter prepared, so that the event can be accepted or rejected based on the
 number of muons which would pass that transverse momentum cut, for instance.
 Note that the filters do not accept or reject *events*, they merely collect
 *lines* that are accepted or rejected by their FilterRules.
 
 Instances of the AutomaticEventFilter class hold a set of
 LHPC::LHEF::FilterRule instances which are used to select which lines of the
 last event read in. to be added to the list, the ParticleLine must pass *all*
 the FilterRules that an AutomaticEventFilter has. More complicated rules than
 the provided "select on transverse momentum", "select on pseudorapidity",
 "select on PDG particle code", and "select on whether initial-state,
 intermediate, or final-state" rules provided can be written as classes derived
 from the FilterRule abstract base class. I hope that the examples in
 LhefParserExample.cpp are clear enough.

 The ParticleLine class provides some static functions to provide sums of
 momenta as lines and transverse momentum sums of these lists of lines.



** LHPC::SlhaParser
   - this class is for reading in data from a file in the SLHA format.

 SLHA1 refers to JHEP 0407 (2004) 036 [hep-ph/0311123], and SLHA2 to
 Comput. Phys. Commun. 180 (2009) 8 [arXiv:0801.0045 [hep-ph]].

 The intended use of SlhaParser is that an instance of the class is
 constructed, and then instances of derived classes of the SlhaBlock class are
 constructed and then registered with the parser with the
 registerBlock( LHPC::SLHA::BaseSlhaBlock const& ) function (but nobody
 should have to deal with the base BaseSlhaBlock class directly).
 
 Registered blocks are filled with data by the next call of
 SlhaParser::readFile( std::string const& slhaFileName ). (Blocks registered
 with a parser that has already read in a file will *not* fill their data until
 the next time a file is read in.)
 
 There are bundles of blocks that automatically register their blocks with the
 SlhaParser given to the bundle's constructor, which cover the blocks described
 in SLHA1 and SLHA2. An instance of LHPC::SlhaOne has all the blocks in SLHA1,
 and an instance of SlhaTwo has all the blocks mentioned in SLHA1 and in SLHA2.
 The entries in the blocks are then filled when readFile( std::string const& )
 is called. The entries are accessed with operator() (various derived classes
 use different numbers of arguments for this) for the copy of their block with
 lowest scale value ("Q"), or the interpreter for a given copy can be accessed
 with operator[], which returns interpreters for the blocks in the order in
 which they were read, starting from 1 (asking for entry 0 returns the
 interpreter for the copy with the lowest scale). Also, the block as a set of
 lines (each line held as a separate std::string) can be obtained by
 getLineWithoutComment( int const ) for each block.

 The function SlhaBlock::hasRecordedScale( double const, int&, int&, double& )
 is the best compromise that I could come up with for finding blocks for a
 given scale. See the comments of the function for how to use it.
 I had intended to provide flexible searching of the blocks as strings to
 accommodate non-standard blocks, but this is still on the to-do list.
 
 Decays are only recorded if a MassSpectrum instance has been registered with
 the SlhaParser (by the registerSpectrum( MassSpectrum& ) function). A
 registered MassSpectrum instance has its MassEigenstate data members filled
 with masses recorded from the MASS or FMASS blocks that are read from the SLHA
 file, and with decays filled from the decays of the file. The particle codes
 of the decays are interpreted so that accessing the decays gets references to
 other MassEigenstates, to simplify following cascade decays for example. It
 includes the distinction between particles and antiparticles (e.g. say a heavy
 boson can decay to a top-antitop pair: this decay is accessed as a reference
 to the top quark paired with a reference to the antitop; the top
 MassEigenstate (under normal circumstances) has then a decay which is accessed
 as a reference to the W^+ MassEigenstate paired with a reference to the bottom
 quark MassEigenstate, while the antitop's decay is the W^- with the
 antibottom).

 The StandardModel class and classes derived from it automatically set up the
 SM particles to have masses and decay widths, along with decay channels and
 branching ratios, as they appeared on the Particle Data Group website
 http://pdg.lbl.gov/ on the 16th of March, 2012. The masses and decays are
 overwritten by any data found in parsed SLHA files.
 
 There is also a LHPC::SlhaSimplisticInterpreter class. An instance of this
 class opens an SLHA file, and tries to match strings as block names followed
 by indices, and returns the string following matched indices in the block, if
 any are found. It is, however, quite inefficient compared to the above, since
 it involves lots of string interpretation with every search.


CHANGELOG:
 * 3rd April 2013: version 0.8.4
 - updated to version 0.4.5 BOLlib (parsing uncommented lines no longer leaves
   trailing newline characters) leading to SlhaSimplisticInterpreter working
   on files without comments for block header lines.

 * 25th March 2013: version 0.8.3
 - updated to version 0.4.4 BOLlib (added explicit #include <unistd.h> to
   WaitingOnSubprocessExecutor.hpp so that it no longer relies on some other
   header including it).

 * 8th March 2013: version 0.8.2
 - updated to version 0.4.3 of BOLlib (fixing bug with XML reader).

 * 15th February 2013: version 0.8.1
 - fixed silly typo in Makefile (several instances of "/PreSelector/" instead
   of "/Preselector/", which was being ignored by my Mac and compiling fine.)
 - updated to version 0.4.2 of BOLlib.

 * 25th January 2013: version 0.8.0
 - fixed LhefEvent::recordEvent( std::string const& eventAsString )
   to allow for the optional information permitted by the LHEF format. all
   characters after the 1st instance of a '#' character are separated from the
   event before parsing, stored in a string accessible by
   LhefEvent::getOptionalInformation().
 - added StandardPreselector class to facilitate common combinations of
   FilterRules for final-state particles. also added
   EitherSignElectronPreselector, EitherSignMuonPreselector, JetPreselector,
   LightLeptonPreselector derived classes for very common desired final states.
 - added example use of the StandardPreselector class and derived classes to
   LhefParserExample.cpp example.
 - update Makefile and READMEs.

 * 15th January 2013: version 0.7.5
 - fixed SlhaSimplisticInterpreter::operator( std::string blockNameAndIndices )
   to correctly return an empty string if given the name of a block that does
   not exist in the SLHAfile, rather than causing a segmentation fault.
 - minor change to Makefile to ensure that it does not return an error if it
   could not remove the file __.SYMDEF, which is sometimes there when unpacking
   libBOLlib.a to incorporate it into libLHPC.a directly.

 * 18th December 2012: version 0.7.4
 - changed Makefile to include all BOLlib source files in libLHPC.a, so only
   -L/path/to/LHPC/ -lLHPC is needed to link the static library, without
   needing to link libBOLlib.a as well.

 * 23rd October 2012: version 0.7.3
 - BOLlib updated to 0.4.1 (minor AsciiXmlParser::loadString signature change)
   
 * 16th October 2012: version 0.7.2
 - BOLlib updated to 0.4.0 (AsciiXmlParser rewritten, now properly ignores XML
   comments) - breaks any code that relies on BOL::AsciiXmlParser, but all LHPC
   files have been updated to use the new code.
 - added
   SlhaSimplisticInterpreter::getLowestScale( std::string const& blockName )
   to return the scale of the copy of the block called blockName with the
   lowest scale.

 * 8th October 2012: version 0.7.1
 - BOLlib updated to 0.3.1 (minor function alias).
 - using above function alias in LhcoParser class.
 - READMEs updated.

 * 5th October 2012: version 0.7.0
 - BOLlib updated to 0.3.0 (BOL::AsciiXmlParser::getCurrentElementAttributes()
   now returns a std::map< std::string, std::string > const& reference).
 - makefile now has deleteobjects option to delete the .o files without
   deleting the library or executables.
 - READMEs updated.
 
 * 4th October 2012: version 0.6.9
 - BOLlib updated to 0.2.2 (reducing thread unsafety)
 - READMEs updated.

 * 28th September 2012: version 0.6.8
 - gave default values of false to verbosities of SLHA block collections
   
 * 28th September 2012: version 0.6.7
 - finished switching verbosity bool references to just bools (0.6.4 did not
   change all of them...)
 
 * 20th September 2012: version 0.6.6
 - removed debugging statements from
   SlhaSimplisticInterpreter::withMap( std::string blockNameAndIndices ).
 - fixed
   SlhaSimplisticInterpreter::operator()( std::string blockNameAndIndices ) to
   correctly only insert whitespace between words of the return string, not
   before the 1st word of the return string as well.

 * 19th September 2012: version 0.6.5
 - BOLlib updated to 0.2.1 (fixing new bug introduced into AsciiXmlParser
   by previous bugfix).

 * 19th September 2012: version 0.6.4
 - changed verbosity bool references to just bools, having decided that the
   ability to switch off verbosity mid-execution isn't worthwhile.
 - BOLlib updated to 0.2.0 (fixing AsciiXmlParser, fixed
   StringParser::stringToIntVector, enhancing ArgumentParser).
 - added withMap( std::string blockNameAndIndices ) function to
   SlhaSimplisticInterpreter, which performs the same job as operator(), but
   checking to see if blockNameAndIndices had already been searched for,
   storing results in a std::map< std::string, std::string >.
 
 * 14th September 2012: version 0.6.3
 - updated SlhaParserExample to demonstrate that SlhaSimplisticInterpreter can
   take strings of indices in floating-point format and also indices can be
   each in their own brackets as well as being separated by commas.
 
 * 13th September 2012: version 0.6.2
 - updated BOLlib to include ArgumentParser class.
 - added LHPC::SlhaSimplisticInterpreter class.
 - fixed makefiles to correctly make lib and bin directories if they are
   missing.
 - corrected READMEs again.
 
 * 10th September 2012: version 0.6.1
 - corrected READMEs.
 
 * 10th September 2012: version 0.6.0
 - reorganized directory structure to be more in line with GNU standards.
 - BOLlib is separate standalone release, but included.
 - Makefiles changed to work with this, also uses full compiler optimization.
 
 * 28th August 2012: version 0.5.0
 - added SparseManyIndexBlock and SparseManyIndex template classes that take
   std::vectors of ints (or convert strings of integers) for map keys.
 - fixed SparseQuadruplyIndexedBlock not actually working (template classes do
   not get compiled by the makefile by default)
 - fixed DenseDoublyIndexedBlock, SparseDoublyIndexedBlock, and
   SparseQuadruplyIndexedBlock, which were returning an implicit cast of the
   result of operator() to a bool for hasEntry().
 
 * 7th August 2012: version 0.4.9
 - added FourMomentum setters.
 - added FourMomentum::toString() for printing the FourMomentum in Cartesian
   co-ordinates.
 - added FourMomentum constructors that take pairs and sum the momenta.
 
 * 3rd August 2012: version 0.4.8
 - fixed StringParser bug (where remainder string was not being updated).
 - added FourMomentum constructors that take vectors or lists and sum the
   momenta.
 
 * 30th July 2012: version 0.4.7
 - fixed bug where FourMomentum::getInvariantMassSquared() and hence also
   FourMomentum::getInvariantMass() were incorrect.
 
 * 28th July 2012: version 0.4.6
 - fixed wrong formula for converting an ObjectLine into a FourMomentum.
 
 * 28th July 2012: version 0.4.5
 - changed FourMomentum assignment functions to not return anything.
 - added angular distance functions to ObjectLine:
   getAzimuthalDistanceTo( ObjectLine const& comparisonObject ) const
   getPseudorapidityDistanceTo( ObjectLine const& comparisonObject ) const
   getPseudorapidityAngularDistanceSquaredTo(
                                     ObjectLine const& comparisonObject ) const
   getPseudorapidityAngularDistanceTo(
                                     ObjectLine const& comparisonObject ) const
 
 * 27th July 2012: version 0.4.4
 - changed ObjectLine::isOrderedByTransverseMomentumLowToHigh( ... ) and
   ObjectLine::isOrderedByTransverseMomentumHighToLow( ... ) to take pointers,
   because LhcoEvents return lists of pointers to ObjectLines, rather than
   lists of ObjectLine objects themselves.
 - also changed the makefile to use optimization level 3 by default (-O3).

 * 26th July 2012: version 0.4.3
 - added LHPC::FourMomentum class to provide basic conversion of ObjectLines
   to four-momenta (also for ParticleLines).
   
 * 16th July 2012: version 0.4.2
 - fixed LhcoEvent erroneously overwriting event number with number of last
   object line.
 
 * 4th July 2012: version 0.4.1
 - fixed LhefEvent counting events from 2 instead of from 1
 - added ObjectLine ordering functions for LHCO:
   ObjectLine::isOrderedByTransverseMomentumLowToHigh( ... ) and
   ObjectLine::isOrderedByTransverseMomentumHighToLow( ... ), suitable for
   being used with std::list::sort( ... ).
 
 * 2nd July 2012: version 0.4.0 released!
 - add LHCO-parsing functionality.
   
 * 22nd May 2012: version 0.3.1
 - fixed segmentation fault bug due to improperly initialized pointer in
   SpectrumUpdater class.

 * 7th April 2012: version 0.3.0 released!
 - New templates (SinglyIndexedMultipleEntriesBlock,
   DoublyIndexedMultipleEntriesBlock, TriplyIndexedMultipleEntriesBlock,
   SparseQuadruplyIndexedBlock, MultipleSinglyIndexed, MultipleDoublyIndexed,
   MultipleTriplyIndexed, SparseQuadruplyIndexed) & classes to go in them
   (RunningConstant, RunningConstantError, FlavorObservable,
   FlavorObservableError) (& the functionality of using
   std::pair< double, double > in the templates is now there) should allow the
   full FLHA to be covered. Does not cover proposed extra column in FOBS (& I
   presume FOBS-type blocks) which specifies if an observable is SM, NP, or
   SM+NP. This could be covered by using TriplyIndexedMultipleEntriesBlock
   instead of DoublyIndexedMultipleEntriesBlock.
   
 * 19th March 2012: version 0.2.2 released!
 - Fixed incorrect command to run ps2epsi from wrong
   "ps2epsi - f LHPC_SpectrumPlotter_LaTeX.ps" to correct
   "ps2epsi LHPC_SpectrumPlotter_LaTeX.ps LHPC_SpectrumPlotter_LaTeX.eps"
   (or path-corrected version).

 * 19th March 2012: version 0.2.1 released!
 - Added the SparseDoublyIndexedBlock class using the SparseDoublyIndexed
   template class as its interpreter.
 - Changed example spectrum-plotting control files to have 'standard' Linux
   paths by default (except in testControl.txt, which still has the paths for
   Mac OSX).
 - Rearranged READMEs and edited the text somewhat.

 * 16th March 2012: version 0.2.0 released!
 - Major reorganization of how the code works behind the scenes, which should
   allow for using the block interpreters for writing input blocks too (by
   setting the values and then calling interpretAsString()).
 - A consequence of the above is that each SlhaParser can have multiple blocks
   registered for any block name. likewise, each SlhaParser can have multiple
   spectra registered.
 - Also changed some names a bit: the block interpreters are now
   SparseSinglyIndexedBlock< double > etc. rather than
   BlockClass::SparseSinglyIndexed< double > and so on.
 - Added hasEntry(...) functions to block interpreters to assist in exploring
   parsed SLHA files without crashing when asking for out-of-range values.
 - Can no longer give a scale to get the closest block to that scale: instead
   hasRecordedScale( double const, int&, int&, double& ) should be used to find
   the pair of blocks nearest with the fraction that can be used to interpolate
   between values from the pair of blocks. Not specifying a scale still
   defaults to getting values from the copy with lowest scale, and now copies
   are accessed in the order that they were recorded.
 (LHEF and SLHA parsers seem to work, spectrum plotter seems to work; after
 some beta testing, this version will be tweaked and released as 1.0.0 - the
 changes of this version represent some of the tweaking foretold below...)

 * 29th February 2012: version 0.1.0 released!
 (LHEF and SLHA parsers seem to work, spectrum plotter seems to work; after
 some beta testing, this version will be tweaked and released as 1.0.0)


The C++ files of LesHouchesParserClasses are:

 <> headers in LHPC/include/:
 LargeHadronColliderOlympicsClasses/FourMomentum.hpp
 LargeHadronColliderOlympicsClasses/LhcoEvent.hpp
 LargeHadronColliderOlympicsClasses/LhcoParser.hpp
 LargeHadronColliderOlympicsClasses/ObjectLine.hpp
 LesHouchesEventFileClasses/AutomaticEventFilter.hpp
 LesHouchesEventFileClasses/FilterRule.hpp
 LesHouchesEventFileClasses/FilterRuleClasses.hpp
 LesHouchesEventFileClasses/InterfaceToClhepLorentzVectorClass.hpp
 LesHouchesEventFileClasses/LhefEvent.hpp
 LesHouchesEventFileClasses/LhefParser.hpp
 LesHouchesEventFileClasses/ParticleLine.hpp
 within LesHouchesEventFileClasses/FilterRuleClasses/:
   - InitialOrIntermediateOrFinalState.hpp
   - ParticleCode.hpp
   - PseudorapidityCut.hpp
   - TransverseMomentumCut.hpp
 MassEigenstateCollectionClasses/DefaultSpectra.hpp
 MassEigenstateCollectionClasses/ExtendedMass.hpp
 MassEigenstateCollectionClasses/MapAndVectorAndBools.hpp
 MassEigenstateCollectionClasses/MassEigenstate.hpp
 MassEigenstateCollectionClasses/MassSpectrum.hpp
 MassEigenstateCollectionClasses/MassSpectrumClasses.hpp
 MassEigenstateCollectionClasses/PointersWithValue.hpp
 MassEigenstateCollectionClasses/RunningConstant.hpp
 MassEigenstateCollectionClasses/RunningConstantError.hpp
 MassEigenstateCollectionClasses/SpectrumUpdater.hpp
 within MassEigenstateCollectionClasses/MassSpectrumClasses/:
 - CodesAndDataForMassEigenstates.hpp
 - MinimalSupersymmetricStandardModel.hpp
 - NextToMinimalSupersymmetricStandardModel.hpp
 - ParticleSpectrumSubsetClasses.hpp
 - StandardModel.hpp
 - ParticleSpectrumSubsetClasses/ChargedSleptonsOneToSix.hpp
 - ParticleSpectrumSubsetClasses/CharginosOneToTwo.hpp
 - ParticleSpectrumSubsetClasses/GluinoOneGeneration.hpp
 - ParticleSpectrumSubsetClasses/MssmExtraEwsbSpinZeroBosonSet.hpp
 - ParticleSpectrumSubsetClasses/NeutralinosOneToFive.hpp
 - ParticleSpectrumSubsetClasses/NeutralinosOneToFour.hpp
 - ParticleSpectrumSubsetClasses/NmssmExtraEwsbSpinZeroBosonSet.hpp
 - ParticleSpectrumSubsetClasses/SneutrinosOneToThree.hpp
 - ParticleSpectrumSubsetClasses/SquarksOneToSix.hpp
 ParticleCodesAndDataClasses/NineDigitSlhaCodes.hpp
 ParticleCodesAndDataClasses/PdgData.hpp
 ParticleCodesAndDataClasses/SevenDigitSlhaCodes.hpp
 SlhaSpectrumPlottingClasses/LineData.hpp
 SlhaSpectrumPlottingClasses/SpectrumDrawer.hpp
 SusyLesHouchesAccordClasses/BlockClasses.hpp
 SusyLesHouchesAccordClasses/BlockTypes.hpp
 SusyLesHouchesAccordClasses/FlavorObservable.hpp
 SusyLesHouchesAccordClasses/FlavorObservableError.hpp
 SusyLesHouchesAccordClasses/FlhaOne.hpp
 SusyLesHouchesAccordClasses/SlhaBlock.hpp
 SusyLesHouchesAccordClasses/SlhaOne.hpp
 SusyLesHouchesAccordClasses/SlhaParser.hpp
 SusyLesHouchesAccordClasses/SlhaTwo.hpp
 SusyLesHouchesAccordClasses/SlhaTwoWithSpheno.hpp
 within SusyLesHouchesAccordClasses/BlockClasses/:
   - BaseSlhaBlock.hpp
   - BaseStringBlock.hpp
   - DenseDoublyIndexedBlock.hpp
   - DenseSinglyIndexedBlock.hpp
   - DenseTriplyIndexedBlock.hpp
   - DoublyIndexedMultipleEntriesBlock.hpp
   - IndexedBlockTemplate.hpp
   - InterpreterClasses.hpp
   - JustSingleValueBlock.hpp
   - LinesAsStringsBlock.hpp
   - SameNameBlockSet.hpp
   - SinglyIndexedMultipleEntriesBlock.hpp
   - SparseDoublyIndexedBlock.hpp
   - SparseQuadruplyIndexedBlock.hpp
   - SparseSinglyIndexedBlock.hpp
   - TriplyIndexedMultipleEntriesBlock.hpp
   - InterpreterClasses/BlockInterpreter.hpp
   - InterpreterClasses/DenseDoublyIndexed.hpp
   - InterpreterClasses/DenseSinglyIndexed.hpp
   - InterpreterClasses/DenseTriplyIndexed.hpp
   - InterpreterClasses/IndexedInterpreter.hpp
   - InterpreterClasses/InterpreterTemplate.hpp
   - InterpreterClasses/JustSingleValue.hpp
   - InterpreterClasses/LinesAsStrings.hpp
   - InterpreterClasses/MultipleDoublyIndexed.hpp
   - InterpreterClasses/MultipleSinglyIndexed.hpp
   - InterpreterClasses/MultipleTriplyIndexed.hpp
   - InterpreterClasses/SparseDoublyIndexed.hpp
   - InterpreterClasses/SparseQuadruplyIndexed.hpp
   - InterpreterClasses/SparseSinglyIndexed.hpp
 LHCO.hpp
 LHEF.hpp
 MassEigenstateCollectionClasses.hpp
 PDG.hpp
 SLHA.hpp
 
 <> source files in LHPC/source/:
 LargeHadronColliderOlympicsClasses/FourMomentum.cpp
 LargeHadronColliderOlympicsClasses/LhcoEvent.cpp
 LargeHadronColliderOlympicsClasses/LhcoParser.cpp
 LargeHadronColliderOlympicsClasses/ObjectLine.cpp
 LesHouchesEventFileClasses/AutomaticEventFilter.cpp
 LesHouchesEventFileClasses/FilterRule.cpp
 LesHouchesEventFileClasses/LhefEvent.cpp
 LesHouchesEventFileClasses/LhefParser.cpp
 LesHouchesEventFileClasses/ParticleLine.cpp
 within LesHouchesEventFileClasses/FilterRuleClasses/:
   - InitialOrIntermediateOrFinalState.cpp
   - ParticleCode.cpp
   - PseudorapidityCut.cpp
   - TransverseMomentumCut.cpp
 MassEigenstateCollectionClasses/ExtendedMass.cpp
 MassEigenstateCollectionClasses/MassEigenstate.cpp
 MassEigenstateCollectionClasses/MassSpectrum.cpp
 MassEigenstateCollectionClasses/RunningConstant.cpp
 MassEigenstateCollectionClasses/RunningConstantError.cpp
 MassEigenstateCollectionClasses/SpectrumUpdater.cpp
 within MassEigenstateCollectionClasses/MassSpectrumClasses/:
 - MinimalSupersymmetricStandardModel.cpp
 - NextToMinimalSupersymmetricStandardModel.cpp
 - StandardModel.cpp
 - ParticleSpectrumSubsetClasses/ChargedSleptonsOneToSix.cpp
 - ParticleSpectrumSubsetClasses/CharginosOneToTwo.cpp
 - ParticleSpectrumSubsetClasses/GluinoOneGeneration.cpp
 - ParticleSpectrumSubsetClasses/MssmExtraEwsbSpinZeroBosonSet.cpp
 - ParticleSpectrumSubsetClasses/NeutralinosOneToFive.cpp
 - ParticleSpectrumSubsetClasses/NeutralinosOneToFour.cpp
 - ParticleSpectrumSubsetClasses/NmssmExtraEwsbSpinZeroBosonSet.cpp
 - ParticleSpectrumSubsetClasses/SneutrinosOneToThree.cpp
 - ParticleSpectrumSubsetClasses/SquarksOneToSix.cpp
 ParticleCodesAndDataClasses/NineDigitSlhaCodes.cpp
 ParticleCodesAndDataClasses/PdgData.cpp
 ParticleCodesAndDataClasses/SevenDigitSlhaCodes.cpp
 SlhaSpectrumPlottingClasses/LineData.cpp
 SlhaSpectrumPlottingClasses/SpectrumDrawer.cpp
 SusyLesHouchesAccordClasses/FlavorObservable.cpp
 SusyLesHouchesAccordClasses/FlavorObservableError.cpp
 SusyLesHouchesAccordClasses/FlhaOne.cpp
 SusyLesHouchesAccordClasses/SlhaOne.cpp
 SusyLesHouchesAccordClasses/SlhaParser.cpp
 SusyLesHouchesAccordClasses/SlhaTwo.cpp
 SusyLesHouchesAccordClasses/SlhaTwoWithSpheno.cpp
 within SusyLesHouchesAccordClasses/BlockClasses/:
   - BaseSlhaBlock.cpp
   - BaseStringBlock.cpp
   - LinesAsStringsBlock.cpp
   - SameNameBlockSet.cpp
   - InterpreterClasses/BlockInterpreter.cpp
   - InterpreterClasses/LinesAsStrings.cpp
 LhcoParserExample.cpp
 LhefParserExample.cpp
 LhpcSpectrumPlotter.cpp
 SlhaParserExample.cpp
 
 <> and also:
 LHPC_CPP/Makefile
 and README.LHPC_CPP.txt which describes the package (copied as README.txt).
 The files of BOLlib are also included, and are described in
 BOLlib/README.BOLlib.txt.
 The makefile creates four executables in LHPC/bin/:
 LhcoParserExample.exe, a demonstration of the LHCO parser
 LhefParserExample.exe, a demonstration of the LHEF parser
 LhpcSpectrumPlotter.exe, a program that uses gnuplot to plot a mass spectrum
                          from an SLHA file
 SlhaParserExample.exe, a demonstration of the SLHA parser.
 
 
