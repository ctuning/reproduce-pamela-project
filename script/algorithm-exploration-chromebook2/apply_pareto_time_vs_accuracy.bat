call ck rm experiment:algorithm-exploration-slambench-opencl-samsung-chromebook2-plat0-dev0-i40-pareto-time
call ck cp experiment:algorithm-exploration-slambench-opencl-samsung-chromebook2-plat0-dev0-i40 reproduce-pamela-project::algorithm-exploration-slambench-opencl-samsung-chromebook2-plat0-dev0-i40-pareto-time
call ck autotune pipeline:program pipeline_from_file=_setup_program_pipeline_tmp.json @apply_pareto_time_vs_accuracy.json
