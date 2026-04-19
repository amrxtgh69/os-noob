{
  "tests": [
    {
      "name": "simple_test",
      "workload": "workloads/simple.txt",
      "runs": [
        { "algo": "fcfs" },
        { "algo": "sjf" },
        { "algo": "rr", "quantum": 2 }
      ]
    },
    {
      "name": "convoy_test",
      "workload": "workloads/convoy.txt",
      "runs": [
        { "algo": "fcfs" },
        { "algo": "stcf" },
        { 
          "algo": "mlfq",
          "levels": 3,
          "quantum": [2, 4, 8]
        }
      ]
    }
  ]
}
