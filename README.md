# lambda-prism Project

The main aim of this project is to test AWS Lambda function with C++ runtime on Amazon Linux 2 VM. Want to call some solid modeling code to create a simple 3D prism. If this is working, will gain key first hand experience with Lambda function: 1. toolchain setup with legacy C++ libs. these C++ libs are valualbe and virtually impossible to redo with newer languages and developers; 2. lambda function delivery (size, lib list); 3. lambda cold start performance; 4. code performance; 5. input/output.
</p>
If the main aim is achieved, want to integrate this with other AWS services. 1. read/write input/output parameters in DynamoDB; 2. write large solid model data as binary blob in S3, and save ARN as reference in an output parametes.

# Amazon linux 2 VM on WSL
As lambda functions are running on Amazon Linux 2 VMs, we need create the same VM on local Windows machine so that we can do some local testing.
 ## Download Amazon Linux 2 WSL installer from https://github.com/yosukes-dev/AmazonWSL
 ## Unzip the zip file to a temp folder
 ## Install and setup Amazon Linux 2 WSL
 ```bash
wsl -l -v
wsl -s Amazon2
wsl --set-version Amazon2 2
wsl
yum update -y && yum update -y
amazon-linux-extras install -y kernel-ng
yum install -y sudo awscli openssh git zsh util-linux-user passwd tar gcc g++ make
useradd -m zhn
passwd zhnvisudo
#add: zhn     ALL=(ALL)       NOPASSWD: ALL
chsh zhn -s /bin/zsh
su - zhn
curl -L https://raw.github.com/robbyrussell/oh-my-zsh/master/tools/install.sh | sh
vi .zshrc
# add "tonotdo" as the theme for easier git usage
/bin/zsh
yum install cmake3
yum install gcc-c++ libcurl-devel
export CC=gcc
export CXX=g++
yum install zlib-devel zlib-static openssl-devel openssl-static

```

# lambda-prism local-build
This repo build a C++ Lambda function on a local workstation and then deploys it with the CLI.   
A YouTube walk through of this repo can also be found [here](https://youtu.be/LaDrQqrrmrI).

 ## Install Some Dependencies
 ```bash
sudo yum install cmake3
sudo yum install make
sudo yum install zip
sudo yum install build-essential gdb

sudo alternatives --install /usr/local/bin/cmake cmake /usr/bin/cmake 10 \
--slave /usr/local/bin/ctest ctest /usr/bin/ctest \
--slave /usr/local/bin/cpack cpack /usr/bin/cpack \
--slave /usr/local/bin/ccmake ccmake /usr/bin/ccmake \
--family cmake

sudo alternatives --install /usr/local/bin/cmake cmake /usr/bin/cmake3 20 \
--slave /usr/local/bin/ctest ctest /usr/bin/ctest3 \
--slave /usr/local/bin/cpack cpack /usr/bin/cpack3 \
--slave /usr/local/bin/ccmake ccmake /usr/bin/ccmake3 \
--family cmake

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
cd ~
ssh-keygen -t rsa -b 4096
cat ~/.ssh/id_rsa.pub
#add public access key to github repos
git config --global user.email "huili_han@yahoo.com"
git config --global user.name "everetthan"
mkdir ~/git
cd ~/git
git clone git@github.com:everetthan/lambda-prism.git
cd ~/git/lambda-prism
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
result arn: 
```bash
arn:aws:iam::788766113629:role/lambda-prism
```

## Deploy 
We can now deploy the lambda function with the following CLI command.
```bash
aws lambda create-function --function-name lambda-prism \
  --role <specify role arn from previous step here> \
  --runtime provided --timeout 15 --memory-size 128 \
  --handler demo --zip-file fileb://demo.zip
```
result function: 
```bash
77bASiCM0cQ+iz/yxBd/+zd61gkiDgNIDN9bgI7Lm/I=    16616192                arn:aws:lambda:us-east-1:788766113629:function:lambda-prism     lambda-prism    demo    2023-01-04T21:28:17.979+0000    128     c56aa753-02ab-4997-a326-f71ead0c33af    arn:aws:iam::788766113629:role/lambda-prism     provided        PendingThe function is being created.   Creating        15      $LATEST
TRACINGCONFIG   PassThrough
```
After creating the lambda-prism function, the function code can be updated using the following awscli command:
```bash
aws lambda update-function-code \
--function-name lambda-prism \
--region us-east-1 \
--zip-file fileb://demo.zip
```

## Test
```bash
aws lambda invoke --function-name lambda-prism --cli-binary-format raw-in-base64-out --payload '{"location_X": 0, "location_Y": 0, "location_Z": 0, "size_length": 100, "size_width": 100, "size_height": 40}' output.json
```

## References
- [Introducing the C Lambda Runtime](https://aws.amazon.com/blogs/compute/introducing-the-c-lambda-runtime/)
- [C++ Sample Lab](https://github.com/awslabs/aws-lambda-cpp)
- [AWS CLI - Invoke Lambda](https://docs.aws.amazon.com/cli/latest/reference/lambda/invoke.html#examples)
- [AWS CLI - Payload Error](https://stackoverflow.com/questions/60310607/amazon-aws-cli-not-allowing-valid-json-in-payload-parameter)
- [YouTube Walk Through](https://youtu.be/LaDrQqrrmrI)
