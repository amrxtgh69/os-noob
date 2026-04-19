import json
import subprocess

with open("workloads/test.tst") as f:
    data = json.load(f)

for test in data["tests"]:
    workload = test["workload"]
    for run in test["runs"]:
        algo = run["algo"]

        cmd = ["./simulator", "--algo", algo, "--workload", workload]
        # dynamically attach params
        for key, value in run.items():
            if key == "algo":
                continue

            if isinstance(value, list):
                cmd += [f"--{key}"] + list(map(str, value))
            else:
                cmd += [f"--{key}", str(value)]

        subprocess.run(cmd)
