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
#include <CATIPGMBasicTopoOpeItfBldr.h>
//#include <CATSession.h>

#include <PrimitiveData.h>

#include <fstream.h>
using namespace std;

using namespace aws::lambda_runtime;

static CATBody* CreatePrimitive(CATGeoFactory* pFactoryIn, CATSoftwareConfiguration* pCATConfigIn, const PrimitiveData* pData)
{
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
		pCuboid->Run();
		pPrimitive=pCuboid->GetResult();
	}
	CATCatch(CATError, err)
	{
        //std::cerr << err->GetNLSMessage().ConvertToChar() << std::endl;
        //Flush(err);

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
    return (NULL);
}

static bool save(CATBody* pBodyIn, const char* pFileName)
{
	CATGeoFactory* pContainer = NULL;
	CATTry
	{
		pContainer = CATCreateCGMContainer();

		CATCloneManager cloneMan(pContainer, CatCGMFullDuplicate, NULL);
		cloneMan.Add(pBodyIn);
		cloneMan.Run();

        ofstream filetowrite(pFileName, ios::binary);
		
		CATSaveCGMContainer((CATGeoFactory *)pContainer, filetowrite);
	
		filetowrite.close();

		pContainer->Release();
	}
	CATCatch(CATError, err)
	{
//         std::cerr << err->GetNLSMessage().ConvertToChar() << std::endl;
//         Flush(err);

		if (pContainer)
			pContainer->Release();
		return false;
	}
	CATEndTry;

	return true;
}

static void createPrism(double x, double y, double z, double length, double width, double height)
{
	//CATSession *pGlobalSession = CATSession::Create_Session("CATGeoFactoryMngt");

	int status = CATCGMTable(0, 314159);
    printf("CATCGMTable returns status = %d\n", status);
#ifdef _DEBUG
    CATLibStatus lib_status = CATPutEnv("CATDictionaryPath=/home/zhn/git/lambda-prism/ThirdParty/CGM_R425/linux_a64/code/dictionary");
    assert(lib_status==CATLibSuccess);
#endif

    //basic container create
    CATIPGMBasicTopoOpeItfBldr* pBasicTopoOpeItfBldr = CATCGMGetBasicTopoOpeItfBldr();
    assert(pBasicTopoOpeItfBldr != NULL);
    
      
	CATGeoFactory * pFactory = CATSGMC1GeoUtilities::CATCreateC1CGMContainer();
	CATSoftwareConfiguration* pConfig = CATCreateSoftwareConfiguration();
	PrimitiveData data(x, y, z, length, width, height);
	CATBody* pBody = CreatePrimitive(pFactory, pConfig, &data);

	save(pBody, "/tmp/prism2.ncgm");

	CATCloseCGMContainer(pFactory);
	pFactory = NULL;
	// if (pGlobalSession)
	// {
	//     CATSession::Delete_Session( pGlobalSession->Get_Id_Session() );
	//     pGlobalSession = NULL;
	// }
}

static invocation_response my_handler(invocation_request const& request)
{
    using namespace Aws::Utils::Json;

    JsonValue json_request(request.payload);
    if (!json_request.WasParseSuccessful()) {
        return invocation_response::failure("Failed to parse input JSON", "InvalidJSON");
    }

    auto request_view = json_request.View();

    if (request_view.ValueExists("location")) {
        
		double x = request_view.GetDouble("location_X");
		double y = request_view.GetDouble("location_Y");
		double z = request_view.GetDouble("location_Z");
		double l = request_view.GetDouble("size_length");
		double w = request_view.GetDouble("size_width");
		double h = request_view.GetDouble("size_height");
		

		createPrism(x, y, z, l, w, h);

        JsonValue response;
        response.WithString("given_loaction", request_view.GetString("location"));
        return invocation_response::success(response.View().WriteCompact(), "application/json");
    } else {
        return invocation_response::failure("'location' not in payload", "InvalidJSON");
    }
}

int main()
{
	//setenv("AWS_LAMBDA_RUNTIME_API","0",1);

#ifdef _DEBUG
	createPrism(0,0,0,100,100,40);
#else
    run_handler(my_handler);
#endif
    return 0;
}
