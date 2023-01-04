<?xml version="1.0" encoding="UTF-8"?>
<!-- WARNING: YWE 15:07:06 SINGLE-CODE 2013x => NO LOCAL CHANGE EXPECTED - USE IMPORT -->
<xsl:stylesheet version="2.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform" xmlns:fo="http://www.w3.org/1999/XSL/Format" xmlns:xs="http://www.w3.org/2001/XMLSchema" xmlns:fn="http://www.w3.org/2005/02/xpath-functions" xmlns:xdt="http://www.w3.org/2005/02/xpath-datatypes">
  <?xml-stylesheet type="text/xsl" href="CoexMetricSection.xsl"?>
  <xsl:output method="html" indent="yes" encoding="UTF-8"/>
   <xsl:variable name="MaxTime">
    <xsl:value-of select="TimeLog/Proc[@Depth = '1']/@Duration"/>
  </xsl:variable>
 
 <xsl:template match="TimeLog">
    <!-- COPYRIGHT DASSAULT SYSTEMES 2013 -->
   <html>
      <head>
     </head>
     <xsl:if test="count(ProcIn)!=0">
       <table class="frame" width="100%">
         <!-- LEVEL1: TABLE OBJECTS PROCESSED -->
           <tr>
           <td> Il y a des <xsl:value-of select="count(ProcIn)"/> ProcIn           </td>
             <td>
               Il y a des <xsl:value-of select="count(ProcOut)"/> ProcOut
             </td>
           </tr>
       </table>

     </xsl:if>
       <table class="frame" xwidth="100%" border="1" CELLPADDING="0" CELLSPACING="0">
  <TR>
    <TD BGCOLOR="LIGHTGRAY"> &#160; Name &#160; </TD>
    <TD BGCOLOR="LIGHTGRAY"> &#160; Time &#160; </TD>
    <TD BGCOLOR="LIGHTGRAY"><CENTER> &#160; Duration &#160; <BR>(second)</BR></CENTER></TD>
  
  </TR>
         <xsl:for-each select="//Proc[@Flux='In' or (@Flux='Out' and  @Duration !='0')]">
              <tr BGCOLOR="" onmouseover="this.bgColor='#D8E3EB'" onmouseout="this.bgColor=''">
              <TD>
      <xsl:if test="@Depth='2'">&#160; &#160; &#160; </xsl:if>
      <xsl:if test="@Depth='3'">&#160; &#160; &#160; &#160; &#160; &#160; </xsl:if>
      <xsl:if test="@Depth='4'">&#160; &#160; &#160; &#160; &#160; &#160; &#160; &#160; &#160; </xsl:if>
      <xsl:if test="@Depth='5'">&#160; &#160; &#160; &#160; &#160; &#160; &#160; &#160; &#160; &#160; &#160; &#160; &#160; &#160; &#160;</xsl:if>
      <xsl:if test="@Depth='6'">&#160; &#160; &#160; &#160; &#160; &#160; &#160; &#160; &#160; &#160; &#160; &#160; &#160; &#160; &#160; &#160; &#160; &#160;</xsl:if>
      <xsl:if test="@Depth='7'">&#160; &#160; &#160; &#160; &#160; &#160; &#160; &#160; &#160; &#160; &#160; &#160; &#160; &#160; &#160; &#160; &#160; &#160; &#160; &#160; &#160;</xsl:if>
      <xsl:if test="@Depth='8'">&#160; &#160; &#160; &#160; &#160; &#160; &#160; &#160; &#160; &#160; &#160; &#160; &#160; &#160; &#160; &#160; &#160; &#160; &#160; &#160; &#160; &#160; &#160; &#160;</xsl:if>
                <xsl:if test="@Flux='In' and @Depth!='1'">
          <IMG SRC="Data/xRight.gif" WIDTH="16"></IMG> 
      </xsl:if>
        <xsl:if test="@Flux='Out' and @Depth!='1' and @Duration !='0'">
          <IMG SRC="Data/xLeft.gif" WIDTH="16"></IMG>  
       </xsl:if>
        &#160; <xsl:value-of select="@Name"/>  &#160; 
             </TD>
             
         <xsl:if test="@Flux='In'">         
             <TD COLSPAN="2"> &#160; <xsl:value-of select="@Time"/>  &#160; </TD>
       </xsl:if>
         <xsl:if test="@Flux='Out' and @Duration !='0'">         
             <TD COLSPAN="1">  &#160; <xsl:value-of select="@Time"/> &#160; </TD>
       </xsl:if>
        
        <xsl:if test="@Flux='BOF'">
       <TD><xsl:value-of select="@Depth"/>  </TD>
        </xsl:if>
      
     <xsl:if test="count(@Duration)!=0 and @Duration !='0'">
        <xsl:variable name="HTime">
        <xsl:value-of select="@Duration*4"/>
      </xsl:variable>
    <xsl:if test="$MaxTime > $HTime">
 
         <TD ALIGN="RIGHT"><xsl:value-of select="@Duration"/> &#160; </TD>
        </xsl:if>
             
       <xsl:if test="$HTime >= $MaxTime">
      <TD BGCOLOR="RED" ALIGN="RIGHT"><xsl:value-of select="@Duration"/>  &#160; </TD>
      </xsl:if>
       </xsl:if>

            </tr>
         </xsl:for-each>
        </table>

 
     <!-- ====================================================== -->
<!-- Final message & CopyRight ============================ -->
<!-- ====================================================== -->
    </html>
   <!-- End of 'Execution' template -->
  </xsl:template>
</xsl:stylesheet>
