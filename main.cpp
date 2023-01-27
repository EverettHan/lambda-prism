#include <stdio.h>
#include <stdlib.h>

#include <aws/lambda-runtime/runtime.h>
#include <aws/core/utils/json/JsonSerializer.h>
#include <aws/core/utils/memory/stl/SimpleStringStream.h>


#include <CATBody.h>
#include <CATSoftwareConfiguration.h>
#include <CATTopData.h>
#include <CATMathPoint.h>
#include <CATGeoFactory.h>
#include <CATICGMTopOperator.h>
#include <CATErrorMacros.h>
#include <CATICGMSolidCuboid.h>
#include <CATCGMContainerMngt.h>
#include <CATGeoFactoryMngt.h>
#include <CATCloneManager.h> 
#include <CATSGMC1GeoUtilities.h>
#include <CATCGMStream.h>
#include <CATCGMNoMoreMemory.h>
#include <CATCGMTable.h>
#include <CATLib.h>
//#include <CATIPGMBasicTopoOpeItfBldr.h>
//#include <CATISGMGeometricObjItfBldr.h>

#include <PrimitiveData.h>

#include <fstream.h>
using namespace std;

using namespace aws::lambda_runtime;

#define TRACE_ERR(...) { fprintf(stderr, __VA_ARGS__); fflush(stderr); }

//#define _DEBUG

static CATBody* CreatePrimitive(CATGeoFactory* pFactoryIn, CATSoftwareConfiguration* pCATConfigIn, const PrimitiveData* pData)
{
    TRACE_ERR("Running in CreatePrimitive() \n")

	CATBody * pPrimitive=NULL;

	CATTopData topData(pCATConfigIn);
	double width = pData->getWidth();
	double length = pData->getLength();
	double height = pData->getHeight();
	CATICGMTopOperator * pOperator=NULL;
	CATTry
	{
		CATMathPoint iPt1(pData->getX()-width/2.0, pData->getY()-length/2.0, pData->getZ());
		CATMathPoint iPt2(iPt1.GetX()+width, iPt1.GetY(), iPt1.GetZ());
		CATMathPoint iPt3(iPt1.GetX(), iPt1.GetY()+length, iPt1.GetZ());
		CATMathPoint iPt4(iPt1.GetX(), iPt1.GetY(), iPt1.GetZ()+height);
		CATICGMSolidCuboid * pCuboid=CATCGMCreateSolidCuboid(pFactoryIn, &topData, iPt1, iPt2, iPt3, iPt4);
		pOperator=pCuboid;

        TRACE_ERR("\t To run CATCGMCreateSolidCuboid operator \n")

		pCuboid->Run();

        TRACE_ERR("\t Finished running CATCGMCreateSolidCuboid operator \n")

		pPrimitive=pCuboid->GetResult();

        if(pPrimitive)
            TRACE_ERR("\t Non-null primitive body created from CATCGMCreateSolidCuboid operator \n")
        else
            TRACE_ERR("\t NULL body created from CATCGMCreateSolidCuboid operator \n")

	}
	CATCatch(CATError, err)
	{
        TRACE_ERR("\t Exception is thrown. The error message is: %s \n", err->GetMessageText())

		if (pPrimitive) 
		{
			pPrimitive->GetContainer()->Remove(pPrimitive);
			pPrimitive=NULL;
		}
	}
	CATEndTry;
	if (pOperator) 
		pOperator->Release();

	return (pPrimitive);
}

static bool save(CATBody* pBodyIn, const char* pFileName)
{
    TRACE_ERR("Running in save() \n")
	CATGeoFactory* pContainer = NULL;
	CATTry
	{
		pContainer = CATCreateCGMContainer();

        TRACE_ERR("\t Called  CATCreateCGMContainer() \n")

		CATCloneManager cloneMan(pContainer, CatCGMFullDuplicate, NULL);
		cloneMan.Add(pBodyIn);
		cloneMan.Run();
        
        TRACE_ERR("\t Body is cloned \n")

        ofstream filetowrite(pFileName, ios::binary);
		
		CATSaveCGMContainer((CATGeoFactory *)pContainer, filetowrite);
	
		filetowrite.close();

        if (!filetowrite)
            TRACE_ERR("\t Failed writing the body into ofstream \n")

		pContainer->Release();
	}
	CATCatch(CATError, err)
	{
        TRACE_ERR("\t Exception is thrown. The error message is: %s \n", err->GetMessageText())
        //TRACE_ERR("\t Exception is thrown. The error message is: %s \n", err->GetNLSMessage().ConvertToChar())
        

		if (pContainer)
			pContainer->Release();
		return false;
	}
	CATEndTry;

	return true;
}

static void createPrism(double x, double y, double z, double length, double width, double height)
{
    TRACE_ERR("Running in createPrism() \n")
  
    TRACE_ERR("\t To call CATCreateCGMContainer \n")  
    CATGeoFactory * pFactory = CATCreateCGMContainer();
    if(pFactory != NULL)
        TRACE_ERR("\t Successfully getting pFactory = %p \n", (void*)pFactory)
    else
        TRACE_ERR("\t Failed getting pFactory \n")

    TRACE_ERR("\t To call CATCreateSoftwareConfiguration \n")  
	CATSoftwareConfiguration* pConfig = CATCreateSoftwareConfiguration();
    if(pConfig != NULL)
        TRACE_ERR("\t Successfully getting pConfig = %p \n", (void*)pConfig)
    else
        TRACE_ERR("\t Failed getting pConfig \n")

    TRACE_ERR("\t To call CreatePrimitive \n")  
	PrimitiveData data(x, y, z, length, width, height);
	CATBody* pBody = CreatePrimitive(pFactory, pConfig, &data);
    if(pBody != NULL)
        TRACE_ERR("\t Successfully getting pBody = %p \n", (void*)pBody)
    else
        TRACE_ERR("\t Failed getting pBody \n")
    
#ifdef _DEBUG
	save(pBody, "prism2.ncgm");
#else
	save(pBody, "/mnt/ws/CGM_R425/prism2.ncgm");
#endif

	CATCloseCGMContainer(pFactory);
	pFactory = NULL;
}

static invocation_response my_handler(invocation_request const& request)
{
    TRACE_ERR("Running in my_handler() \n")

    using namespace Aws::Utils::Json;

    JsonValue json_request(request.payload);
    if (!json_request.WasParseSuccessful()) {
        return invocation_response::failure("Failed to parse input JSON", "InvalidJSON");
    }

    auto request_view = json_request.View();

    if (request_view.ValueExists("location_X")) {
        
        TRACE_ERR("\t parsing payload data \n")
		double x = request_view.GetDouble("location_X");
		double y = request_view.GetDouble("location_Y");
		double z = request_view.GetDouble("location_Z");
		double l = request_view.GetDouble("size_length");
		double w = request_view.GetDouble("size_width");
		double h = request_view.GetDouble("size_height");
		

        TRACE_ERR("\t parsed payload data: x=%f, y=%f, z=%f, l=%f, w=%f, h=%f \n", x,y,z,l,w,h);
		createPrism(x, y, z, l, w, h);

        JsonValue response;
        response.WithString("lambda_prism2 return Status", "done");
        return invocation_response::success(response.View().WriteCompact(), "application/json");
    } else {
        return invocation_response::failure("'location' not in payload", "InvalidJSON");
    }
}

void initializeCGM()
{
    TRACE_ERR("Running in initializeCGM() \n")

    int status = CATCGMTable(0, 314159);
    printf("CATCGMTable returns status = %d\n", status);
#ifdef _DEBUG
    CATPutEnv("CATDictionaryPath=/home/zhn/git/lambda-prism/ThirdParty/CGM_R425/linux_a64/code/dictionary");    
#endif

    const char *pDicPath   = CATGetEnv("CATDictionaryPath");
    TRACE_ERR("\t CATDictionaryPath is set at: %s \n", pDicPath);
    
    TRACE_ERR("\t To call CATCreateCGMContainer \n")  
    CATGeoFactory * pFactory = CATCreateCGMContainer();
    if(pFactory != NULL)
        TRACE_ERR("\t Successfully getting pFactory = %p \n", (void*)pFactory)
    else
        TRACE_ERR("\t Failed getting pFactory \n")

    
	CATCloseCGMContainer(pFactory);
}

int main()
{
    TRACE_ERR("Running in main() \n")

#ifdef _DEBUG
	createPrism(0,0,0,100,100,40);
#else

	initializeCGM();
    TRACE_ERR("\t Calling my_handler() \n")
    run_handler(my_handler);
#endif
    return 0;
}
