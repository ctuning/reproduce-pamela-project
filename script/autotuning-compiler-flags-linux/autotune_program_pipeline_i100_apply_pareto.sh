ck cp experiment:pamela-autotune-flags-slambench-linux-i100 :pamela-autotune-flags-slambench-linux-pareto
ck autotune pipeline:program pipeline_from_file=_setup_program_pipeline_tmp.json @autotune_program_pipeline_i100_apply_pareto.json
