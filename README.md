# lambda-prism Project

The main aim of this project is to test AWS Lambda function with C++ runtime on Amazon Linux 2 VM. Want to call some solid modeling code to create a simple 3D prism. If this is working, will gain key first hand experience with Lambda function: 1. toolchain setup with legacy C++ libs. these C++ libs are valualbe and virtually impossible to redo with newer languages and developers; 2. lambda function delivery (size, lib list); 3. lambda cold start performance; 4. code performance; 5. input/output.
</p>
If the main aim is achieved, want to integrate this with other AWS services. 1. read/write input/output parameters in DynamoDB; 2. write large solid model data as binary blob in S3, and save ARN as reference in an output parametes.

# lambda-prism local-build
This repo build a C++ Lambda function on a local workstation and then deploys it with the CLI.   
A YouTube walk through of this repo can also be found [here](https://youtu.be/LaDrQqrrmrI).

 ## Install Some Dependencies
 ```bash
sudo yum install cmake3
sudo yum install make
sudo yum install zip
```

## Build the AWS C++ SDK
These steps install the C++ SDK into the `~/install` directory and clones all the directories into `~`. This can obviously be altered if desired.    
We are also only installing the `core` package. Other packages may be required for more involved Lambda functions. 
```bash
mkdir ~/install
cd ~
git clone https://github.com/aws/aws-sdk-cpp.git
cd aws-sdk-cpp
mkdir build
cd build
cmake3 .. -DBUILD_ONLY="core" \
  -DCMAKE_BUILD_TYPE=Release \
  -DBUILD_SHARED_LIBS=OFF \
  -DENABLE_UNITY_BUILD=ON \
  -DCUSTOM_MEMORY_MANAGEMENT=OFF \
  -DCMAKE_INSTALL_PREFIX=~/install \
  -DENABLE_UNITY_BUILD=ON
make
make install
```

## Build the AWS C++ Lambda Runtime
```bash
cd ~
git clone https://github.com/awslabs/aws-lambda-cpp-runtime.git
cd aws-lambda-cpp-runtime
mkdir build
cd build
cmake .. -DCMAKE_BUILD_TYPE=Release \
  -DBUILD_SHARED_LIBS=OFF \
  -DCMAKE_INSTALL_PREFIX=~/install
make
make install
```

## Build the Actual C++ Lambda Function
```bash
git clone git@github.com:everetthan/lambda-prism.git
cd ~/lambda-prism
mkdir build
cd build
cmake3 .. -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=~/install
make
make aws-lambda-package-demo
```

## Make IAM Role for the Lambda Function
We need to create and IAM role that the can be attached to the lambda function when it is deployed. Note the rights in this role may need to be expanded for more complex Lambda functions.  
First create a JSON file that defines the required permissions as shown below.
```JSON
{
  "Version": "2012-10-17",
  "Statement": [
    {
      "Effect": "Allow",
      "Principal": {"Service": ["lambda.amazonaws.com"]},
      "Action": "sts:AssumeRole"
    }
  ]
}
```
Then create the IAM role in the CLI as shown below.
```bash
aws iam create-role --role-name lambda-prism --assume-role-policy-document file://trust-policy.json
```
The output of the above command will include the ARN of the new role. You must copy this ARN. It will be required when you deploy the Lambda function. It will most like have the form `arn:aws:iam::<your AWS account number>:role/lambda-prism`.   

Next attached the `AWSLambdaBasicExecutionRole` policy to the new role to allow the Lambda function to write to CloudWatch Logs. This is performed with the following CloudWatch command.
```bash 
aws iam attach-role-policy --role-name lambda-prism --policy-arn arn:aws:iam::aws:policy/service-role/AWSLambdaBasicExecutionRole
```

## Deploy 
We can now deploy the lambda function with the following CLI command.
```bash
aws lambda create-function --function-name demo \
  --role <specify role arn from previous step here> \
  --runtime provided --timeout 15 --memory-size 128 \
  --handler demo --zip-file fileb://demo.zip
```

## Test
```bash
aws lambda invoke --function-name demo --cli-binary-format raw-in-base64-out --payload '{"location_X": 0, "location_Y": 0, "location_Z": 0, "size_length": 100, "size_width": 100, "size_height": 40}' output.json
```

## References
- [Introducing the C Lambda Runtime](https://aws.amazon.com/blogs/compute/introducing-the-c-lambda-runtime/)
- [C++ Sample Lab](https://github.com/awslabs/aws-lambda-cpp)
- [AWS CLI - Invoke Lambda](https://docs.aws.amazon.com/cli/latest/reference/lambda/invoke.html#examples)
- [AWS CLI - Payload Error](https://stackoverflow.com/questions/60310607/amazon-aws-cli-not-allowing-valid-json-in-payload-parameter)
- [YouTube Walk Through](https://youtu.be/LaDrQqrrmrI)
