ck rm experiment:pamela-autotune-flags-slambench-linux-i10-pareto
ck cp experiment:pamela-autotune-flags-slambench-linux-i10 :pamela-autotune-flags-slambench-linux-i10-pareto
ck autotune pipeline:program pipeline_from_file=_setup_program_pipeline_tmp.json @autotune_program_pipeline_i10_apply_pareto.json
