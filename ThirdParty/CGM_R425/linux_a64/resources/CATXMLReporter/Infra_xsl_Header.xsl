<?xml version="1.0" encoding="UTF-8"?>
<!-- WARNING: YWE 15:07:06 SINGLE-CODE 2013x => NO LOCAL CHANGE EXPECTED - USE IMPORT -->
<xsl:stylesheet version="2.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform" xmlns:fo="http://www.w3.org/1999/XSL/Format" xmlns:xs="http://www.w3.org/2001/XMLSchema" xmlns:fn="http://www.w3.org/2005/02/xpath-functions" xmlns:xdt="http://www.w3.org/2005/02/xpath-datatypes">
  <xsl:include href="Infra_xsl_DataSource.xsl"/>
  <xsl:include href="Infra_xsl_MetricsOptions.xsl"/>
  <xsl:include href="Infra_xsl_HeaderNotifications.xsl"/>
  <xsl:include href="Infra_xsl_Notifications.xsl"/>

  <xsl:output method="html" indent="yes" encoding="UTF-8"/>


  <xsl:variable name="iconHSize">18</xsl:variable>

  <xsl:variable name="TabSeparator"><tr><td height="6"></td></tr></xsl:variable>
  <xsl:variable name="DSVersion">
    <xsl:value-of select="Execution/Set/Set[@Name = 'ExecutionMetrics']/Metric[@Name='Version']/@value"/>
  </xsl:variable>
  <xsl:variable name="ProcessName">
    <xsl:value-of select="Execution/@Name"/>
  </xsl:variable>
  <xsl:variable name="EndReplayDate">
    <xsl:value-of select="Execution/Set/Set[@Name = 'ExecutionMetrics']/Metric[@Name='EndReplayDate']/@value"/>
  </xsl:variable>
  <xsl:variable name="GlobalReturnCodeIcon">Data/<xsl:value-of select="Execution/Set[@Name='Resource']/Metric[@Name='GlobalReturnCodeIcon']/@value"/></xsl:variable>
  <xsl:variable name="GlobalReturnCodeAbstract"><xsl:value-of select="Execution/Set[@Name='Resource']/Metric[@Name='GlobalReturnCodeIcon']/@nls"/></xsl:variable>
  <xsl:variable name="GlobalProgressionValue"><xsl:value-of select="Execution/Set[@Name='Resource']/Metric[@Name='GlobalProgressionValue']/@value"/></xsl:variable>
  <xsl:variable name="LinkOnOfficialDoc"><xsl:value-of select="Execution/Set[@Name='Resource']/Metric[@Name='LinkOnOfficialDoc']/@value"/></xsl:variable>
  <xsl:variable name="LinkOnOfficialAbstract"><xsl:value-of select="Execution/Set[@Name='Resource']/Metric[@Name='LinkOnOfficialDoc']/@Name"/></xsl:variable>
  <xsl:variable name="NameColumn"><xsl:value-of select="Execution/Set[@Name='Resource']/Metric[@Name='NameColumn']/@nls"/></xsl:variable>
  <xsl:variable name="ValueColumn"><xsl:value-of select="Execution/Set[@Name='Resource']/Metric[@Name='ValueColumn']/@nls"/></xsl:variable>
  <xsl:variable name="StatisticsFor"><xsl:value-of select="Execution/Set[@Name='Resource']/Metric[@Name='StatisticsFor']/@nls"/></xsl:variable>
  <xsl:variable name="ResultsFor"><xsl:value-of select="Execution/Set[@Name='Resource']/Metric[@Name='ResultsFor']/@nls"/></xsl:variable>
  <xsl:variable name="DetailsFor"><xsl:value-of select="Execution/Set[@Name='Resource']/Metric[@Name='DetailsFor']/@nls"/></xsl:variable>
  <xsl:variable name="Objects"><xsl:value-of select="Execution/Set[@Name='Resource']/Metric[@Name='Objects']/@nls"/></xsl:variable>
  <xsl:variable name="Report"><xsl:value-of select="Execution/Set[@Name='Resource']/Metric[@Name='Report']/@nls"/></xsl:variable>
  <xsl:variable name="ReplayDate"><xsl:value-of select="Execution/Set[@Name='Resource']/Metric[@Name='ReplayDate']/@nls"/></xsl:variable>

  <xsl:template name="InfraHeader">
      <!-- 1- Initialization -->
      <!--   1-1 HTML header -->


     <body link="#0000FF" vlink="#800080" BGCOLOR="white" background="Data/PLMBatch_DSBackground.jpg" bgproperties="fixed">
       <style>
         .Entete {font: 40 pt bold; color: blue; text-align: center}
         .Menu {font: 20 pt; text-align: right; text-align: bottom}
         .Normal {font: 12pt bold;	text-align: left;color: red; text-align: bottom}
         .Normal2 {font: 20pt bold;	text-align: left; color: green; text-align: bottom}
         .Parameter {font: 14pt; color:red; text-align: left;font-style:italic}
         .Input { font-weight:bold;font-family="Arial";color:#314292;font-size=15;background-color: #D8D8D8;}
         .Comment { font-weight:bold;font-family="Arial";color:blue;font-size=15;background-color: #D8D8D8;}
         .hyperlink{font-weight:bold;font-family="Arial";color:blue;font-size=12}
       </style>
  </body>

<!-- BEGIN MAIN HEADER AND BANNER -->
<table border="0" width="100%" height="80" cellpadding="0" cellspacing="0" background="Data/PLMBatch_DSBanner.jpg">
  <TR><TD width="75"></TD>
  <TD xwidth="1000">
    <!-- BEGIN-IMG01 THE RETURN CODE -->
   <IMG ALIGN="RIGHT" HEIGHT="45">
          <xsl:attribute name="SRC"><xsl:copy-of select="$GlobalReturnCodeIcon" /></xsl:attribute>            
          <xsl:attribute name="alt"><xsl:copy-of select="$GlobalReturnCodeAbstract" /></xsl:attribute>            
      </IMG>
    <!-- ENDOF-IMG01 THE RETURN CODE -->
    <I><B><font SIZE="+2" COLOR="WHITE"><xsl:value-of select="$ProcessName"/><xsl:text> </xsl:text><xsl:value-of select="$Report"/>
    </font></B></I>
    </TD>
  <TD align="right" width="250"><font size="-1" COLOR="WHITE">
        Version<xsl:value-of select="@version"/>
        <BR><xsl:value-of select="$ReplayDate"/><xsl:copy-of select="$EndReplayDate" /></BR>
  </font></TD>
    <TD WIDTH="45">
      <xsl:if test="$LinkOnOfficialDoc != ''"><!-- BEGIN-IMG02 LINK ON DOC WHEN ANY -->
      <A>
      <xsl:attribute name="href"><xsl:copy-of select="$LinkOnOfficialDoc" /></xsl:attribute>
      <xsl:attribute name="alt"><xsl:copy-of select="$LinkOnOfficialAbstract" /></xsl:attribute>            
      <IMG ALIGN="RIGHT" src="Data/PLMBatch_iconInfo.jpg" border="0" ></IMG>
      </A>
      </xsl:if><!-- ENDOF-IMG02 LINK ON DOC WHEN ANY -->
    </TD>
  </TR>
</table>
<!-- ENDOF MAIN HEADER AND BANNER -->


<!-- BEGIN PROGRESSION VALUE AND STEP -->
    <table border="0" WIDTH="100%" CELLPADDING="0" CELLSPACING="0">
     <xsl:if test="$GlobalProgressionValue &lt; 100">
     <xsl:copy-of select="$TabSeparator" />
       <tr>
         <td>
           <table class="frame" width="100%" bgcolor="lightgray">
             <!-- LEVEL1: TABLE PROGRESSION-->
             <tr>
               <td width="40" rowspan="1">
                 <IMG SRC="Data/Infra_Icon_Process.gif" ALIGN="LEFT" HEIGHT="45"></IMG>
               </td>
               <th valign="middle" class="titleMode">
                 <font size="+1">
                   <blink>
                     <xsl:value-of select="./Set[@Name='Resource']/Metric[@Name='GlobalProgressionValue']/@nls"/> 
                     <xsl:copy-of select="$GlobalProgressionValue" /> % 
                     <br></br>
                     <xsl:value-of select="./Set[@Name='Resource']/Metric[@Name='GlobalProgressionStep']/@nls"/>
                     <xsl:value-of select="./Set[@Name='Resource']/Metric[@Name='GlobalProgressionStep']/@value"/>
                   </blink>
                 </font>
               </th>
             </tr>
           </table>
         </td>
       </tr>
     </xsl:if>
 </table> 
<!-- ENDOF PROGRESSION VALUE AND STEP -->       

  </xsl:template>

  <xsl:template name="InfraFooter">
     <HR COLOR="orange"></HR>
     <P align="right"><I>
         Copyright DASSAULT SYSTEMES SA 2014 - <xsl:copy-of select="$DSVersion" />
          - Visit us at: <A href="http://www.3ds.com">www.3ds.com</A>
     </I></P>

  </xsl:template>

  <xsl:template name="InfraHeaderGlobalMetrics">
         <!-- LEVEL0: TABLE with DATASOURCE-METRICSandOPTIONS-->
     <table border="0" bordercolor="ORANGE" WIDTH="100%" CELLPADDING="0" CELLSPACING="0">
     <!-- GlobalMetrics.1 - Display list of Fatal/Error Notification -->
            <xsl:copy-of select="$TabSeparator" />
            <xsl:call-template name="HeaderInfraNotifications"/>   <!-- include Infra_xsl_HeaderNotifications.xsl -->
     <!-- GlobalMetrics.2 - Providers connections -->
            <xsl:copy-of select="$TabSeparator" />
            <xsl:call-template name="InfraDataSource"/>   <!-- include Infra_xsl_DataSource.xsl -->
     <!-- GlobalMetrics.3 - Metrics & conditions -->
     <!-- GlobalMetrics.3.1 - Metrics & conditions -->
     <!-- GlobalMetrics.3.2 - Options -->
     <!-- GlobalMetrics.3.3 - Environment Variables -->
            <xsl:copy-of select="$TabSeparator" />
            <xsl:call-template name="InfraMetricOptions"/> <!-- include Infra_xsl_MetricsOptions.xsl -->
       </table>
       <P></P>
  </xsl:template>
</xsl:stylesheet>
