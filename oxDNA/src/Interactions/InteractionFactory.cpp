/*
 * InteractionFactory.cpp
 *
 *  Created on: Feb 13, 2013
 *      Author: rovigatti
 */

#include "InteractionFactory.h"

#include "../PluginManagement/PluginManager.h"

#include "DNAInteraction.h"
#include "DNAInteraction_nomesh.h"
#include "RNAInteraction.h"
#include "LJInteraction.h"
#include "PatchyInteraction.h"
#include "PatchyInteractionDan.h"
#include "KFInteraction.h"
#include "DNAInteraction_relax.h"
#include "TSPInteraction.h"
#include "HSInteraction.h"
#include "DHSInteraction.h"
#include "BoxInteraction.h"
#include "HardCylinderInteraction.h"
#include "HardSpheroCylinderInteraction.h"
#include "CustomInteraction.h"
#include "DNA2Interaction.h"
#include "RNAInteraction2.h"
#include "RNAInteraction_relax.h"
#include "TEPInteraction.h"
#include "JordanInteraction.h"
#include "ACInteraction.h"
#include "ACTInteraction.h"
#include "DNANMInteraction.h"
#include "DNANMInteraction_relax.h"
#include "RNANMInteraction.h"
#include "DNACTInteraction.h"
#include "RNACTInteraction.h"

InteractionFactory::InteractionFactory() {

}

InteractionFactory::~InteractionFactory() {

}

template<typename number>
IBaseInteraction<number> *InteractionFactory::make_interaction(input_file &inp) {
	// The default interaction is DNAInteraction
	std::string inter_type ("DNA");
	getInputString(&inp, "interaction_type", inter_type, 0);

	if(inter_type.compare("DNA") == 0) {
		// in order to avoid small mismatches between potential energies computed on the GPU and
		// on the CPU we enforce the DNAInteraction_nomesh interaction class
		std::string backend ("");
		getInputString(&inp, "backend", backend, 0);
		if(backend.compare("CUDA") == 0) return new DNAInteraction_nomesh<number>();
		else return new DNAInteraction<number>();
	}
	else if(inter_type.compare("DNA2") == 0) {
		std::string backend ("");
		getInputString(&inp, "backend", backend, 0);
		if(backend.compare("CUDA") == 0) return new DNA2Interaction_nomesh<number>();
		else return new DNA2Interaction<number>();
	}
	else if(inter_type.compare("DNA_nomesh") == 0) return new DNAInteraction_nomesh<number>();
	else if(inter_type.compare("DNA2_nomesh") == 0) return new DNA2Interaction_nomesh<number>();
	else if(inter_type.compare("LJ") == 0) return new LJInteraction<number>();
	else if(inter_type.compare("DNA_relax") == 0) return new DNAInteraction_relax<number>();
	else if(inter_type.compare("RNA") == 0) return new RNAInteraction<number>();
	else if(inter_type.compare("patchy") == 0) return new PatchyInteraction<number>();
	else if(inter_type.compare("patchyDan") == 0) return new PatchyInteractionDan<number>();
	else if(inter_type.compare("KF") == 0) return new KFInteraction<number>();
	else if(inter_type.compare("TSP") == 0) return new TSPInteraction<number>();
	else if(inter_type.compare("HS") == 0) return new HSInteraction<number>();
	else if(inter_type.compare("Box") == 0) return new BoxInteraction<number>();
	else if(inter_type.compare("HardCylinder") == 0) return new HardCylinderInteraction<number>();
	else if(inter_type.compare("HardSpheroCylinder") == 0) return new HardSpheroCylinderInteraction<number>();
	else if(inter_type.compare("DHS") == 0) return new DHSInteraction<number>();
	else if(inter_type.compare("custom") == 0) return new CustomInteraction<number>();
	else if(inter_type.compare("DNA2") == 0) return new DNA2Interaction<number>();
	else if(inter_type.compare("RNA2") == 0) return new RNA2Interaction<number>();
	else if(inter_type.compare("RNA_relax") == 0) return new RNAInteraction_relax<number>();
	else if(inter_type.compare("TEP") == 0) return new TEPInteraction<number>();
	else if(inter_type.compare("Jordan") == 0) return new JordanInteraction<number>();
	else if(inter_type.compare("AC") == 0) return new ACInteraction<number>();
	else if(inter_type.compare("DNANM") == 0) return new DNANMInteraction<number>();
	else if(inter_type.compare("ACT") == 0) return new ACTInteraction<number>();
	else if(inter_type.compare("RNANM") == 0) return new RNANMInteraction<number>();
	else if(inter_type.compare("DNANM_relax") == 0) return new DNANMInteraction_relax<number>();
	else if(inter_type.compare("DNACT") == 0) return new DNACTInteraction<number>();
	else if(inter_type.compare("RNACT") == 0) return new RNACTInteraction<number>();
	else {
		IBaseInteraction<number> *res = PluginManager::instance()->get_interaction<number>(inter_type);
		if(res == NULL) throw oxDNAException ("Interaction '%s' not found. Aborting", inter_type.c_str());
		return res;
	}
}

template IBaseInteraction<float> *InteractionFactory::make_interaction<float>(input_file &inp);
template IBaseInteraction<double> *InteractionFactory::make_interaction<double>(input_file &inp);
