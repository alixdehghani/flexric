#include <stdio.h>
#include <json-c/json.h>
#include <assert.h>

// Function to add key-value pairs to a JSON object
void json_add_object(json_object* obj, const char* key, json_object* value) {
    assert(obj != NULL);
    assert(key != NULL);
    assert(value != NULL);

    json_object_object_add(obj, key, value);
}

// Function to add an integer array to a JSON object
void json_array_add_int(json_object* array, int value) {
    assert(array != NULL);
    json_object_array_add(array, json_object_new_int(value));
}

// Function to add boolean values to JSON arrays
// void json_array_add_bool(json_object* array, bool value) {
//     assert(array != NULL);
//     json_object_array_add(array, json_object_new_boolean(value));
// }


int main(){
    json_object* root = json_object_new_object();

    /*** Constructing SIB1 ***/
    json_object* sib1 = json_object_new_object();
    json_add_object(sib1, "cell_barred", json_object_new_string("notBarred"));
    json_add_object(sib1, "intra_freq_reselection", json_object_new_string("allowed"));
    json_add_object(sib1, "p_max", json_object_new_int(23));
    json_add_object(sib1, "q_rx_lev_min", json_object_new_int(-70));

    // Constructing sched_info array
    json_object* sched_info_array = json_object_new_array();
    json_object* sched_info = json_object_new_object();

    // Adding si_mapping_info array
    json_object* si_mapping_info = json_object_new_array();
    json_array_add_int(si_mapping_info, 3);
    json_array_add_int(si_mapping_info, 5);
    json_array_add_int(si_mapping_info, 6);
    json_add_object(sched_info, "si_mapping_info", si_mapping_info);

    json_add_object(sched_info, "si_periodicity", json_object_new_int(16));
    json_array_add_int(sched_info_array, (int) json_object_get_int(sched_info));
    json_add_object(sib1, "sched_info", sched_info_array);

    json_add_object(sib1, "si_window_length", json_object_new_int(20));
    json_add_object(sib1, "system_info_value_tag", json_object_new_int(8));

    json_add_object(root, "sib1", sib1);

    /*** Constructing SIB2 ***/
    json_object* sib2 = json_object_new_object();

    // freqInfo
    json_object* freqInfo = json_object_new_object();
    json_add_object(freqInfo, "additional_spectrum_emission", json_object_new_int(1));
    json_add_object(freqInfo, "ul_bw_present", json_object_new_boolean(1));
    json_add_object(freqInfo, "ul_carrier_freq_present", json_object_new_boolean(1));

    json_add_object(sib2, "freqInfo", freqInfo);

    // rr_config_common_sib
    json_object* rr_config_common_sib = json_object_new_object();

    // bcch_cnfg
    json_object* bcch_cnfg = json_object_new_object();
    json_add_object(bcch_cnfg, "modification_period_coeff", json_object_new_int(16));
    json_add_object(rr_config_common_sib, "bcch_cnfg", bcch_cnfg);

    // pcch_cnfg
    json_object* pcch_cnfg = json_object_new_object();
    json_add_object(pcch_cnfg, "default_paging_cycle", json_object_new_int(32));
    json_add_object(pcch_cnfg, "nB", json_object_new_string("1"));
    json_add_object(rr_config_common_sib, "pcch_cnfg", pcch_cnfg);

    // pdsch_cnfg
    json_object* pdsch_cnfg = json_object_new_object();
    json_add_object(pdsch_cnfg, "p_b", json_object_new_int(1));
    json_add_object(pdsch_cnfg, "rs_power", json_object_new_int(0));
    json_add_object(rr_config_common_sib, "pdsch_cnfg", pdsch_cnfg);

    // prach_cnfg
    json_object* prach_cnfg = json_object_new_object();
    json_object* prach_cnfg_info = json_object_new_object();
    json_add_object(prach_cnfg_info, "high_speed_flag", json_object_new_boolean(0));
    json_add_object(prach_cnfg_info, "prach_config_index", json_object_new_int(6));
    json_add_object(prach_cnfg_info, "prach_freq_offset", json_object_new_int(7));
    json_add_object(prach_cnfg_info, "zero_correlation_zone_config", json_object_new_int(11));

    json_add_object(prach_cnfg, "prach_cnfg_info", prach_cnfg_info);
    json_add_object(prach_cnfg, "root_sequence_index", json_object_new_int(204));
    json_add_object(rr_config_common_sib, "prach_cnfg", prach_cnfg);

    // pucch_cnfg
    json_object* pucch_cnfg = json_object_new_object();
    json_add_object(pucch_cnfg, "delta_pucch_shift", json_object_new_int(1));
    json_add_object(pucch_cnfg, "n1_pucch_an", json_object_new_int(12));
    json_add_object(pucch_cnfg, "n_cs_an", json_object_new_int(0));
    json_add_object(pucch_cnfg, "n_rb_cqi", json_object_new_int(1));
    json_add_object(rr_config_common_sib, "pucch_cnfg", pucch_cnfg);

    // pusch_cnfg
    json_object* pusch_cnfg = json_object_new_object();
    json_add_object(pusch_cnfg, "enable_64_qam", json_object_new_boolean(0));
    json_add_object(pusch_cnfg, "hopping_mode", json_object_new_string("interSubFrame"));
    json_add_object(pusch_cnfg, "n_sb", json_object_new_int(1));
    json_add_object(pusch_cnfg, "pusch_hopping_offset", json_object_new_int(2));

    json_object* ul_rs = json_object_new_object();
    json_add_object(ul_rs, "cyclic_shift", json_object_new_int(0));
    json_add_object(ul_rs, "group_assignment_pusch", json_object_new_int(0));
    json_add_object(ul_rs, "group_hopping_enabled", json_object_new_boolean(0));
    json_add_object(ul_rs, "sequence_hopping_enabled", json_object_new_boolean(0));

    json_add_object(pusch_cnfg, "ul_rs", ul_rs);
    json_add_object(rr_config_common_sib, "pusch_cnfg", pusch_cnfg);

    json_add_object(sib2, "rr_config_common_sib", rr_config_common_sib);

    json_add_object(root, "sib2", sib2);

    // Print JSON output
    printf("Generated JSON:\n%s\n", json_object_to_json_string_ext(root, JSON_C_TO_STRING_PRETTY));

    // Free JSON objects
    json_object_put(root);

    return 0;
}