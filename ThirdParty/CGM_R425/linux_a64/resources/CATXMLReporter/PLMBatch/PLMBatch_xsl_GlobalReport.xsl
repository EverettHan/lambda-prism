<?xml version="1.0" encoding="UTF-8"?>
<!-- WARNING: YWE 15:07:06 SINGLE-CODE 2013x => NO LOCAL CHANGE EXPECTED - USE IMPORT -->
<xsl:stylesheet version="2.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform" xmlns:fo="http://www.w3.org/1999/XSL/Format" xmlns:xs="http://www.w3.org/2001/XMLSchema" xmlns:fn="http://www.w3.org/2005/02/xpath-functions" xmlns:xdt="http://www.w3.org/2005/02/xpath-datatypes">
  <?xml-stylesheet type="text/xsl" href="CoexMetricSection.xsl"?>
  <xsl:output method="html" indent="yes" encoding="UTF-8"/>
  <xsl:include href="Infra_xsl_Header.xsl"/>
 <!-- <xsl:include href="Coex_xsl_ObjectReport.xsl"/> -->
 
  <!-- COPYRIGHT DASSAULT SYSTEMES 2013 -->
    <xsl:template match="Execution">
   <html>
      <head>
       <link rel="stylesheet" type="text/css" href="Data/ReportFBDI.css"/>
       <script id="scripttag" type="text/javascript" src="Data/ReportFBDI.js"></script>
     </head>
<!-- ====================================================== -->
<!-- Initial Header & initialization ====================== -->
<!-- ====================================================== -->
   <xsl:call-template name="InfraHeader"/>                 <!-- include Infra_xsl_Header.xsl -->
<!-- ====================================================== -->
<!-- Providers - Metrics & Options ======================== -->
<!-- ====================================================== -->
   <xsl:call-template name="InfraHeaderGlobalMetrics"/>    <!-- include Infra_xsl_Header.xsl -->
 
   <xsl:if test="count(//Object)!=0">
        <table class="frame" width="100%">
          <!-- LEVEL1: TABLE OBJECTS PROCESSED -->
          <tr>
            <th class="titleMode" onmouseover="this.className='highlightTitleMode clickable';"
                                onmouseout="this.className='titleMode clickable';"
                                onclick="toggle_visibility_by_id('Objects','plusminusObjects')">
              Details for <xsl:value-of select="count(//Object)"/> Objects 
              <img src="Data\Minus.gif" class="clickable" id="plusminusObjects">
                <xsl:attribute name="height"><xsl:copy-of select="$iconHSize" /></xsl:attribute>
              </img>
            </th>
          </tr>
             
             
          <tr>
            <td>                 
            <span id="Objects" class="xdisplayHide">
      <!--       <table width="100%" border="2" bordercolor="RED"><tr><td>     -->     
    <!--         <xsl:call-template name="ObjectHeaderStat"/>  -->   <!-- include Coex_xsl_ObjectReport.xsl -->                  
       <!--       <xsl:copy-of select="$TabSeparator" />      -->    <!-- var defined in Infra_xsl_Header.xsl -->   
              <br></br>
              <!--     <xsl:call-template name="CoexObjectResultTab"/>  -->   <!-- include Coex_xsl_ObjectReport.xsl -->                  
               <br></br>
              <!--
             <xsl:call-template name="ObjectNavigationTab"/>  
             --> <!-- include Coex_xsl_ObjectReport.xsl -->                  
       <!--        </td></tr></table>       -->        
            </span>
               
                   
            </td>
          </tr>
        </table>
         
        </xsl:if>         
          

<!-- ====================================================== -->
<!-- Final message & CopyRight ============================ -->
<!-- ====================================================== -->
     <xsl:call-template name="InfraFooter"/>               <!-- include Infra_xsl_Header.xsl -->  
   </html>
   </xsl:template>
   <!-- End of 'Execution' template -->



  
  
  

</xsl:stylesheet>
