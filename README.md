# lambda-prism

The main aim of this project is to test AWS Lambda function with C++ runtime on Amazon Linux 2 VM. Want to call some solid modeling code to create a simple 3D prism. If this is working, will gain key first hand experience with Lambda function: 1. toolchain setup with legacy C++ libs. these C++ libs are valualbe and virtually impossible to redo with newer languages and developers; 2. lambda function delivery (size, lib list); 3. lambda cold start performance; 4. code performance; 5. input/output.
</p>
If the main aim is achieved, want to integrate this other AWS services. 1. read/write input/output parameters in DynamoDB; 2. write large solid model data as binary blob in S3, and save ARN as reference in output parameters.
