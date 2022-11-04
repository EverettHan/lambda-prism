# lambda-prism

The main aim of this project is to test AWS Lambda function with C++ runtime on Amazon Linux 2 VM. Want to call some solid modeling code to create a simple 3D prism. If this is working, will learn many things: 1. first hand experience with Lambda function - toolchain setup with legacy libs; 2. lambda function delivery (size, lib list); 3. lambda cold start performance; 4. code performance; 5. input/output.
If the main aim is achieved, want to integrate this other AWS services. 1. read/write input/output parameters in DynamoDB; 2. write large solid model data as binary blob in S3, and save ARN as reference in output parameters.
