#include <stdio.h>
#include <stdlib.h>

#include <aws/lambda-runtime/runtime.h>
#include <aws/core/utils/json/JsonSerializer.h>
#include <aws/core/utils/memory/stl/SimpleStringStream.h>

#include <CATBody.h>
#include <CATSoftwareConfiguration.h>
#include <CATTopData.h>
#include <CATMathPoint.h>
#include <CATMathVector.h>
#include <CATMathAxis.h>
#include <CATMathPlane.h>
#include <CATMathBox.h>
#include <CATGeoFactory.h>
#include <CATICGMTopOperator.h>
#include <CATErrorMacros.h>
#include <CATICGMSolidCuboid.h>
#include <CATICGMSolidCylinder.h>
#include <CATICGMTopRevol.h>
#include <CATICGMSolidSphere.h>
#include <CATICGMSolidTorus.h>
#include <CATICGMSolidPyramid.h>
#include <CATICGMCloseOperator.h>
#include <CATCGMContainerMngt.h>
#include <CATGeoFactoryMngt.h>
#include <CATCloneManager.h>
#include <CATSGMC1GeoUtilities.h>
#include <CATCGMStream.h>
#include <CATCGMNoMoreMemory.h>
#include <CATCGMTable.h>
#include <CATLib.h>   

#include <CATMath.h>
#include <CATPoint.h>
#include <CATPlane.h>                   // Geometric plane
#include <CATVertex.h>                 // Vertex
#include <CATFace.h>                   // Face   
#include <CATCone.h>                                            
#include <ListPOfCATCell.h>                                           
#include <ListPOfCATFace.h>                                                     
#include <ListPOfCATVertex.h>   
#include <CATCrvLimits.h>          // Limits on a curve
#include <CATPCurve.h>
#include <CATPLine.h>
#include <CATICGMTopSkin.h>                // skin operator
#include <CATTopObject.h>
#include <CATTopology.h>

#include <PrimitiveData.h>

#include <fstream.h>
using namespace std;

using namespace aws::lambda_runtime;

#define TRACE_ERR(...)                \
    {                                 \
        fprintf(stderr, __VA_ARGS__); \
        fflush(stderr);               \
    }

//#define _DEBUG

static void OrderPrimitveFaces(CATBody * piBody, CATMathPoint & origin, CATMathVector & axis, CATLISTP(CATFace) & orderedFaces)
{
    TRACE_ERR("Running in OrderPrimitveFaces() \n")
	// process face sequence, if exist, the first is the from face and the last is to face
	// lateral faces should be ordered by the from face
	//CATLISTP(CATFace) faces;
	//piBody->GetAllCells((CATLISTP(CATCell)&) faces, 2);
    CATLISTP(CATCell) faces;
	piBody->GetAllCells(faces, 2);
	CATFace * ptFromFace=NULL, * ptToFace=NULL;
	double resolution=piBody->GetContainer()->GetResolution(CatC0);
    for(int item=1;item<=faces.Size();++item)
	{
        CATFace* pFace = (CATFace*)faces[item];
		CATPlane * ptPlane=(CATPlane *) pFace->GetSurface();
		if(ptPlane->IsATypeOf(CATPlaneType))
		{
			CATMathPoint planeOrigin; 
			CATMathVector planeNormal;
			ptPlane->GetNormal(planeOrigin, planeNormal);
			if(planeNormal.IsParallel(axis))
			{
				CATMathVector dvec=(planeOrigin-origin);
				dvec.Normalize();
				if(fabs(dvec*planeNormal)<resolution) 
				{
					//ptFromFace=faces[item];
					ptFromFace=pFace;
					orderedFaces.Append(ptFromFace);
				}
				else
				{
                    //ptToFace=faces[item];
                    ptToFace=pFace;
                }
                    
				faces.RemovePosition(item);
				item--;
				if(ptToFace && ptFromFace)
					break;
			}
		}
	}
	// assume the lateral faces are ordered properly from construction sequence
	//orderedFaces.Append(faces);
    for(int item=1;item<=faces.Size();++item)
	{
        CATFace* pFace = (CATFace*)faces[item];
        orderedFaces.Append(pFace);
    }
	if(ptToFace)
		orderedFaces.Append(ptToFace);
}

static CATBody *CreatePrimitive(CATGeoFactory *pFactoryIn, CATSoftwareConfiguration *pCATConfigIn, const PrimitiveData *pData)
{
    TRACE_ERR("Running in CreatePrimitive() \n")

	CATTopData topData(pCATConfigIn);
	CATMathPoint origin(pData->getX(), pData->getY(), pData->getZ());
	double width = pData->getWidth();
	double length = pData->getLength();
	double height = pData->getHeight();
	CATICGMTopOperator * pOperator=NULL;
	CATBody* pPrimitive=NULL;
	CATMathDirection axis(0.,0.,1.);
	CATTry
	{
		PrimitiveType primitiveType = pData->getPrimitiveType();
		switch(primitiveType)
		{
		case PrimitiveType::Cuboid:	//cuboid: origin defines the center point of base face
		case PrimitiveType::Pyramid:   //pyramid: use cuboid base face
			{
				CATMathPoint iPt1(origin.GetX()-width/2.0, origin.GetY()-length/2.0, origin.GetZ());
				CATMathPoint iPt2(iPt1.GetX()+width, iPt1.GetY(), iPt1.GetZ());
				CATMathPoint iPt3(iPt1.GetX(), iPt1.GetY()+length, iPt1.GetZ());
				CATMathPoint iPt4(iPt1.GetX(), iPt1.GetY(), iPt1.GetZ()+height);
				CATICGMSolidCuboid * pCuboid=CATCGMCreateSolidCuboid(pFactoryIn, &topData, iPt1, iPt2, iPt3, iPt4);
				pOperator=pCuboid;
				pCuboid->Run();
				pPrimitive=pCuboid->GetResult();
				if(primitiveType == PrimitiveType::Pyramid) // use the base face to create final shape
				{
					CATLISTP(CATFace) orderedFaces;
					OrderPrimitveFaces(pPrimitive, origin, axis, orderedFaces);
					pOperator->Release();
					CATICGMSolidPyramid * pPyramidOp=CATCGMCreateSolidPyramid(pFactoryIn, &topData, orderedFaces[1], origin+axis*height);
					pOperator=pPyramidOp;
					pPyramidOp->Run();
					pFactoryIn->Remove(pPrimitive);
					pPrimitive=pPyramidOp->GetResult();
				}
			}
			break;
		case PrimitiveType::Cylinder: // cylinder: width is diameter
            {
                CATMathPoint topCenter(origin.GetX(), origin.GetY(), origin.GetZ()+height);
                double radius=width/2.0;

                // Create operator to create cylinder
                CATICGMSolidCylinder* pCylinderOp = CATCGMTopCreateSolidCylinder(pFactoryIn, &topData, origin, topCenter, radius);
                if (pCylinderOp != NULL)
                    TRACE_ERR("\t Successfully getting pCylinderOp = %p \n", (void *)pCylinderOp)
                else
                    TRACE_ERR("\t Failed getting pCylinderOp \n")

                // Run the operator and return the result.
                pOperator=pCylinderOp;
				pCylinderOp->Run();
				pPrimitive = pCylinderOp->GetResult();
            }
            break;
		case PrimitiveType::Cone:	// cone: width is diameter, height locates apex
			{
				CATMathPoint iBaseCenter = origin;
                CATMathPoint iTopCenter(origin.GetX(), origin.GetY(), origin.GetZ()+height);
                double iBottomRadius = width;
                double iTopRadius = 0.;

                double truncatedHeight = (iTopCenter-iBaseCenter).Norm();

                //The truncated height is same as full cone height in the case when top radius is zero.
                double fullConeHeight = truncatedHeight;
                // Calculate the full cone height when top radius is greater than zero.
                if(iTopRadius > 0)
                {
                    fullConeHeight = truncatedHeight * iBottomRadius / (iBottomRadius - iTopRadius);
                }

                CATMathPoint apex = iTopCenter;
                // Calculate the Apex of the full cone in case the full cone height is greater than the truncated height.
                double ratio = fullConeHeight / truncatedHeight;
                if(ratio > 1.0)
                {
                    apex = iBaseCenter + (iTopCenter - iBaseCenter) * ratio;
                }

                // Computes cone parameters
                CATMathVector coneNormal = apex - iBaseCenter;
                CATMathDirection axisK(coneNormal);
                CATMathDirection axisI(CATMathI);
                if ( axisI.IsParallel(axisK) )
                {
                    axisI = CATMathJ;
                }
                CATMathDirection axisJ(axisK ^ axisI);
                axisI = axisK ^ axisJ;
                CATMathAxis coneAxis(apex, axisI, axisJ, -axisK);
                fullConeHeight = coneNormal.Norm();
                double coneAngle = CATAtan(fullConeHeight/iBottomRadius);
                double endRuledLength(fullConeHeight/sin(coneAngle));
                double startRuledLength = endRuledLength * iTopRadius / iBottomRadius;

                // Create a cone geometry
                // If an exception is thrown in this workflow, the CGMFactoryRemovable_uptr object will remove this object from the container.
                CATCone* pMyCone = pFactoryIn->CreateCone(coneAxis, 0.0, coneAngle, 0.0, CAT2PI, startRuledLength, endRuledLength);
                

                // Ensure that the object will not be deleted by reference counting
                // until it is explicitly removed from the container.
                pMyCone->SetMode( CatCGMExplicit );

                // Create a sheet cone
                // Note: Recall that the GetLimits method may not always return the expected limits.
                // We can use it here since we have just created the surface and there has been
                // no chance for the limits to be reset by another operation.
                CATSurLimits surLimits;
                pMyCone->GetLimits(surLimits);

                CATICGMTopSkin* pSkinOp = CATCGMCreateTopSkin(pFactoryIn, &topData, pMyCone, &surLimits);
                
                pOperator=pSkinOp;
				pSkinOp->Run();
                CATBody *sheetCone = pSkinOp->GetResult();                
                pOperator->Release();

                if (NULL != sheetCone)
                {
                    CATICGMCloseOperator* pCloseOp = CATCGMCreateCloseOperator(pFactoryIn, &topData, sheetCone);
                    
                    pOperator=pCloseOp;
                    pCloseOp->Run();
                    pPrimitive = pCloseOp->GetResult();
                }
			}
			break;
		case PrimitiveType::Sphere: // sphere: width is diameter
			{
				CATICGMSolidSphere * pSphereOp=CATCGMCreateSolidSphere(pFactoryIn, &topData, origin, width/2.0);
				pOperator=pSphereOp;
				pSphereOp->Run();
				pPrimitive = pSphereOp->GetResult();
			}
			break;
		case PrimitiveType::Torus: // torus: width is major radius, height is minor radius
			{
				CATMathAxis torusAxis(origin, CATMathVector(1,0,0), CATMathVector(0,1,0));
				CATICGMSolidTorus * pTorusOp=CATCGMCreateSolidTorus(pFactoryIn, &topData, torusAxis, origin+CATMathPoint(width/2.0, 0, 0), origin+CATMathPoint(width/2.0, 0, height/2.0));
				pOperator=pTorusOp;
				pTorusOp->Run();
				pPrimitive = pTorusOp->GetResult();
			}
			break;
		default:
			break;
		}
	}
	CATCatch(CATError, error)
	{
		if (pPrimitive) 
		{
			pPrimitive->GetContainer()->Remove(pPrimitive);
			pPrimitive=NULL;
		}
	}
	CATEndTry;

	if (pOperator) 
        pOperator->Release();
        
	return(pPrimitive);
}

static bool save(CATBody *pBodyIn, const char *pFileName)
{
    TRACE_ERR("Running in save() \n")
    CATGeoFactory *pContainer = NULL;
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
        // TRACE_ERR("\t Exception is thrown. The error message is: %s \n", err->GetNLSMessage().ConvertToChar())

        if (pContainer)
            pContainer->Release();
        return false;
    }
    CATEndTry;

    return true;
}


static invocation_response my_handler(invocation_request const &request)
{
    TRACE_ERR("Running in my_handler() \n")

    using namespace Aws::Utils::Json;

    JsonValue json_request(request.payload);
    if (!json_request.WasParseSuccessful())
    {
        return invocation_response::failure("Failed to parse input JSON", "InvalidJSON");
    }

    auto request_view = json_request.View();

    if (request_view.ValueExists("primitive_type"))
    {
        TRACE_ERR("\t parsing payload data \n")
        std::string typeStr = request_view.GetString("primitive_type");
        PrimitiveType primitive_type = PrimitiveType::None;
        if (typeStr == "primitive_cuboid")
            primitive_type = PrimitiveType::Cuboid;
        if (typeStr == "primitive_pyramid")
            primitive_type = PrimitiveType::Pyramid;
        else if (typeStr == "primitive_cylinder")
            primitive_type = PrimitiveType::Cylinder;
        else if (typeStr == "primitive_cone")
            primitive_type = PrimitiveType::Cone;
        else if (typeStr == "primitive_sphere")
            primitive_type = PrimitiveType::Sphere;
        else if (typeStr == "primitive_torus")
            primitive_type = PrimitiveType::Torus;
        else
        {
            TRACE_ERR("\t Wrong primitive_type parameter!!! exception thrown \n")
            return invocation_response::failure("'primitive_type' is wrong", "InvalidJSON");
        }
        double x = request_view.GetDouble("location_X");
        double y = request_view.GetDouble("location_Y");
        double z = request_view.GetDouble("location_Z");
        double l = request_view.GetDouble("size_length");
        double w = request_view.GetDouble("size_width");
        double h = request_view.GetDouble("size_height");
        PrimitiveData data(primitive_type, x, y, z, l, w, h);

        TRACE_ERR("\t To call CATCreateCGMContainer \n")
        CATGeoFactory *pFactory = CATCreateCGMContainer();
        if (pFactory != NULL)
            TRACE_ERR("\t Successfully getting pFactory = %p \n", (void *)pFactory)
        else
            TRACE_ERR("\t Failed getting pFactory \n")

        TRACE_ERR("\t To call CATCreateSoftwareConfiguration \n")
        CATSoftwareConfiguration *pConfig = CATCreateSoftwareConfiguration();
        if (pConfig != NULL)
            TRACE_ERR("\t Successfully getting pConfig = %p \n", (void *)pConfig)
        else
            TRACE_ERR("\t Failed getting pConfig \n")

        TRACE_ERR("\t To call CreatePrimitive \n")
        CATBody *pBody = CreatePrimitive(pFactory, pConfig, &data);
        if (pBody != NULL)
            TRACE_ERR("\t Successfully getting pBody = %p \n", (void *)pBody)
        else
            TRACE_ERR("\t Failed getting pBody \n")

        std::string pathname = "/mnt/ws/CGM_R425/" +  typeStr + ".ncgm";
        save(pBody, pathname.c_str());

        CATCloseCGMContainer(pFactory);
        pFactory = NULL;
    
        JsonValue response;
        response.WithString("lambda_prism2 return Status", "done");
        return invocation_response::success(response.View().WriteCompact(), "application/json");
    }
    else
    {
        return invocation_response::failure("'primitive_type' not in payload", "InvalidJSON");
    }
}

static void runTests()
{
    TRACE_ERR("Running in runTests() \n")

    TRACE_ERR("\t To call CATCreateCGMContainer \n")
    CATGeoFactory *pFactory = CATCreateCGMContainer();
    if (pFactory != NULL)
        TRACE_ERR("\t Successfully getting pFactory = %p \n", (void *)pFactory)
    else
        TRACE_ERR("\t Failed getting pFactory \n")

    TRACE_ERR("\t To call CATCreateSoftwareConfiguration \n")
    CATSoftwareConfiguration *pConfig = CATCreateSoftwareConfiguration();
    if (pConfig != NULL)
        TRACE_ERR("\t Successfully getting pConfig = %p \n", (void *)pConfig)
    else
        TRACE_ERR("\t Failed getting pConfig \n")
    
    {// test 1: Cuboid
        PrimitiveData data(PrimitiveType::Cuboid, 0, 0, 0, 100, 100, 40);
        TRACE_ERR("\t To call CreatePrimitive \n")
        CATBody *pBody = CreatePrimitive(pFactory, pConfig, &data);
        if (pBody != NULL)
        {
            TRACE_ERR("\t Successfully getting cuboid pBody = %p \n", (void *)pBody)
            save(pBody, "cuboid.ncgm");
        }
        else
        {
            TRACE_ERR("\t Failed getting cuboid pBody \n")
        }            
    }
        
    {// test 2: Pyramid
        PrimitiveData data(PrimitiveType::Pyramid, 0, 0, 0, 100, 100, 40);
        TRACE_ERR("\t To call CreatePrimitive \n")
        CATBody *pBody = CreatePrimitive(pFactory, pConfig, &data);
        if (pBody != NULL)
        {
            TRACE_ERR("\t Successfully getting pyramid pBody = %p \n", (void *)pBody)
            save(pBody, "pyramid.ncgm");
        }    
        else
        {
            TRACE_ERR("\t Failed getting pyramid pBody \n")
        }            
    }
        
    {// test 3: Cylinder
        PrimitiveData data(PrimitiveType::Cylinder, 0, 0, 0, 100, 100, 40);
        TRACE_ERR("\t To call CreatePrimitive \n")
        CATBody *pBody = CreatePrimitive(pFactory, pConfig, &data);
        if (pBody != NULL)
        {
            TRACE_ERR("\t Successfully getting cylinder pBody = %p \n", (void *)pBody)
            save(pBody, "cylinder.ncgm");
        }
        else
        {
            TRACE_ERR("\t Failed getting cylinder pBody \n")
        }            
    }
        
    {// test 4: Cone        
        PrimitiveData data(PrimitiveType::Cone, 0, 0, 0, 100, 100, 40);
        TRACE_ERR("\t To call CreatePrimitive \n")
        CATBody *pBody = CreatePrimitive(pFactory, pConfig, &data);
        if (pBody != NULL)
        {
            TRACE_ERR("\t Successfully getting cone pBody = %p \n", (void *)pBody)
            save(pBody, "cone.ncgm");
        }
        else
        {
            TRACE_ERR("\t Failed getting cone pBody \n")
        }
    }
        
    {// test 5: Sphere        
        PrimitiveData data(PrimitiveType::Sphere, 0, 0, 0, 100, 100, 40);
        TRACE_ERR("\t To call CreatePrimitive \n")
        CATBody *pBody = CreatePrimitive(pFactory, pConfig, &data);
        if (pBody != NULL)
        {
            TRACE_ERR("\t Successfully getting sphere pBody = %p \n", (void *)pBody)
            save(pBody, "sphere.ncgm");
        }
        else
        {
            TRACE_ERR("\t Failed getting sphere pBody \n")
        }            
    }
        
    {// test 6: Torus        
        PrimitiveData data(PrimitiveType::Torus, 0, 0, 0, 100, 100, 40);
        TRACE_ERR("\t To call CreatePrimitive \n")
        CATBody *pBody = CreatePrimitive(pFactory, pConfig, &data);
        if (pBody != NULL)
        {
            TRACE_ERR("\t Successfully getting torus pBody = %p \n", (void *)pBody)
            save(pBody, "torus.ncgm");
        }
        else
        {
            TRACE_ERR("\t Failed getting torus pBody \n")
        }
    }

    CATCloseCGMContainer(pFactory);
    pFactory = NULL;
}


static void initializeCGM()
{
    TRACE_ERR("Running in initializeCGM() \n")

    int status = CATCGMTable(0, 314159);
    printf("CATCGMTable returns status = %d\n", status);
#ifdef _DEBUG
    CATPutEnv("CATDictionaryPath=/home/zhn/git/lambda-prism/ThirdParty/CGM_R425/linux_a64/code/dictionary");
#endif

    const char *pDicPath = CATGetEnv("CATDictionaryPath");
    TRACE_ERR("\t CATDictionaryPath is set at: %s \n", pDicPath);

    TRACE_ERR("\t To call CATCreateCGMContainer \n")
    CATGeoFactory *pFactory = CATCreateCGMContainer();
    if (pFactory != NULL)
        TRACE_ERR("\t Successfully getting pFactory = %p \n", (void *)pFactory)
    else
        TRACE_ERR("\t Failed getting pFactory \n")

    CATCloseCGMContainer(pFactory);
}

int main()
{
    TRACE_ERR("Running in main() \n")

    initializeCGM();

#ifdef _DEBUG
    TRACE_ERR("\t Calling runTests() \n")
    runTests();
#else
    TRACE_ERR("\t Calling my_handler() \n")
    run_handler(my_handler);
#endif
    return 0;
}
