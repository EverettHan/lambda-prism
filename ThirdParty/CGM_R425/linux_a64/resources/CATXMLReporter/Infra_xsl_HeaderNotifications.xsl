<?xml version="1.0" encoding="UTF-8"?>
<!-- WARNING: YWE 15:07:06 SINGLE-CODE 2013x => NO LOCAL CHANGE EXPECTED - USE IMPORT -->
<xsl:stylesheet version="2.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform" xmlns:fo="http://www.w3.org/1999/XSL/Format" xmlns:xs="http://www.w3.org/2001/XMLSchema" xmlns:fn="http://www.w3.org/2005/02/xpath-functions" xmlns:xdt="http://www.w3.org/2005/02/xpath-datatypes">
<xsl:output method="html" indent="yes" encoding="UTF-8"/>

  <xsl:variable name="COLORFatal">#FF0000</xsl:variable>
  <xsl:variable name="COLORError">#FF9900</xsl:variable>
  <xsl:variable name="COLORWarning">#CCFF00</xsl:variable>
  <xsl:variable name="COLORDefault"></xsl:variable>

  <!-- ============================================= -->
  <!--  Notification template                        -->
  <!-- ============================================= -->


    <xsl:template match="Notification">
    <!-- TEMPLATE_NOTIFICATION -->
    <!-- Print Attribute Name & Type  -->
    <xsl:choose>
      <xsl:when test="@Sev='Fatal'">
        <tr align="center" bgcolor="000080">
          <td WIDTH="10%"><b><font COLOR="white" FACE="Arial">Severity</font></b></td>
          <td WIDTH="10%"><b><font COLOR="white" FACE="Arial">Type</font></b></td>
          <td WIDTH="80%"><b><font COLOR="white" FACE="Arial">Message</font></b></td>
        </tr>
        <tr><xsl:attribute name="bgcolor"><xsl:copy-of select="$COLORFatal" /></xsl:attribute>
         <xsl:call-template name="HeaderDisplayObjectNotifications"/> <!-- include Infra_xsl_HeaderNotifications.xsl -->
        </tr>
      </xsl:when>
      <xsl:when test="@Sev='Error'">
         <tr align="center" bgcolor="000080">
          <td WIDTH="10%"><b><font COLOR="white" FACE="Arial">Severity</font></b></td>
          <td WIDTH="10%"><b><font COLOR="white" FACE="Arial">Type</font></b></td>
          <td WIDTH="80%"><b><font COLOR="white" FACE="Arial">Message</font></b></td>
        </tr>
       
         <tr><xsl:attribute name="bgcolor"><xsl:copy-of select="$COLORError" /></xsl:attribute>
         <xsl:call-template name="HeaderDisplayObjectNotifications"/> <!-- include Infra_xsl_HeaderNotifications.xsl -->
         </tr>
      </xsl:when>
      <xsl:when test="@Sev='Warning'">
          <tr align="center" bgcolor="000080">
          <td WIDTH="10%"><b><font COLOR="white" FACE="Arial">Severity</font></b></td>
          <td WIDTH="10%"><b><font COLOR="white" FACE="Arial">Type</font></b></td>
          <td WIDTH="80%"><b><font COLOR="white" FACE="Arial">Message</font></b></td>
        </tr>
        <tr><xsl:attribute name="bgcolor"><xsl:copy-of select="$COLORWarning" /></xsl:attribute>
         <xsl:call-template name="HeaderDisplayObjectNotifications"/> <!-- include Infra_xsl_HeaderNotifications.xsl -->
        </tr>
      </xsl:when>
      <xsl:when test="@Sev='Info'">
        <tr bgcolor="#FFFFFF">
          <td colspan="1" valign="top"> <xsl:value-of select="@Name"/> </td>
          <td colspan="2" valign="top"> <xsl:value-of select="@msg"/> </td>
        </tr>
      </xsl:when>
      <xsl:otherwise>
        <!-- For Trace, Debug & Info -->
        <tr bgcolor="#D0D0D0">
        <td><xsl:value-of select="@Sev"/> </td>
        <td><xsl:value-of select="@Name"/></td>
        <td><xsl:value-of select="@msg"/> </td>
        </tr>
      </xsl:otherwise>
    </xsl:choose>
    <!-- End of 'Notification' template -->
  </xsl:template>


  <xsl:template name="HeaderInfraNotifications">
    <!-- From Higher to Lower severity -->
    <xsl:variable name="ErrorType">
      <xsl:choose>
        <xsl:when test="count(./Notification[@Sev='Error'])!=0">11</xsl:when>
        <xsl:otherwise>
          <xsl:choose>
            <xsl:when test="count(./Set/Object/Notification[@Sev='Error'])!=0">12</xsl:when>
            <xsl:otherwise>
              <xsl:choose>
                <xsl:when test="count(./Set/Object/Engine/Notification[@Sev='Error'])!=0">13</xsl:when>
                <xsl:otherwise>
                  <xsl:choose>
                    <xsl:when test="count(./Set/Notification[@Sev='Error'])!=0">14</xsl:when>
                  </xsl:choose>
                </xsl:otherwise>
              </xsl:choose>
            </xsl:otherwise>
          </xsl:choose>
        </xsl:otherwise>
      </xsl:choose>
      <xsl:choose>
        <xsl:when test="count(./Notification[@Sev='Fatal'])!=0">1</xsl:when>
        <xsl:otherwise>
          <xsl:choose>
            <xsl:when test="count(./Set/Object/Notification[@Sev='Fatal'])!=0">2</xsl:when>
            <xsl:otherwise>
              <xsl:choose>
                <xsl:when test="count(./Set/Object/Engine/Notification[@Sev='Fatal'])!=0">3</xsl:when>
                <xsl:otherwise>
                  <xsl:choose>
                    <xsl:when test="count(./Set/Notification[@Sev='Fatal'])!=0">4</xsl:when>
                  </xsl:choose>
                </xsl:otherwise>
              </xsl:choose>
            </xsl:otherwise>
          </xsl:choose>
        </xsl:otherwise>
      </xsl:choose>
      <xsl:choose>
        <xsl:when test="count(./Notification[@Sev='Warning'])!=0">-1</xsl:when>
      </xsl:choose>

    </xsl:variable>

    <xsl:variable name="ErrorMode">
      <xsl:choose>
        <xsl:when test="count(./Notification[@Sev='Fatal' or @Sev='Error'])!=0">1</xsl:when>
        <xsl:otherwise>
          <xsl:choose>
            <xsl:when test="count(./Set/Object/Engine/Notification[@Sev='Fatal' or @Sev='Error'])!=0">2</xsl:when>
            <xsl:otherwise>
              <xsl:choose>
                <xsl:when test="count(./Set/Object/Notification[@Sev='Fatal' or @Sev='Error'])!=0">2</xsl:when>
                <xsl:otherwise>
                  <xsl:choose>
                    <xsl:when test="count(./Set/Notification[@Sev='Fatal' or @Sev='Error'])!=0">2</xsl:when>
                  </xsl:choose>
                </xsl:otherwise>
              </xsl:choose>
            </xsl:otherwise>
          </xsl:choose>
        </xsl:otherwise>
      </xsl:choose>
      <xsl:choose>
        <xsl:when test="count(./Notification[@Sev='Warning' ])!=0">-1</xsl:when>
      </xsl:choose>
    </xsl:variable>
 

    <!-- Template: Execution Options --> 
    <xsl:if test="$ErrorType > 0">

      <!-- Return the main return Code -->
      <tr>
        <td>
          <!--          ErrorType=<xsl:copy-of select="$ErrorType" /> - ErrorMode=<xsl:copy-of select="$ErrorMode" /> -->
          <table class="frame" width="100%" bgcolor="red">
          <tr>
            <!-- Display the main return Code icon if any - else display the default  -->
<!--            <th class="titleMode" WIDTH="20" VALIGN="top">
              <IMG ALIGN="LEFT" HEIGHT="45">
                  <xsl:attribute name="SRC"><xsl:copy-of select="$GlobalReturnCodeIcon" /></xsl:attribute>            
                  <xsl:attribute name="alt"><xsl:copy-of select="$GlobalReturnCodeIcon" /></xsl:attribute>            
              </IMG>
          </th>
 -->         
            <th>
              <table xclass="frame" width="100%" bgcolor="red">
                <tr>
                  <th class="titleMode">
                    <xsl:value-of select="./Set[@Name='GlobalInformation']/Set[@Name='ExecutionMetrics']/Metric[@Name='GlobalReturnCode']/@nls"/>
                    =
                    <xsl:value-of select="./Set[@Name='GlobalInformation']/Set[@Name='ExecutionMetrics']/Metric[@Name='GlobalReturnCode']/@value"/>
                  </th>
                </tr>
              </table>


              <xsl:if test="$ErrorMode = 1">
                <table xclass="frame" width="100%" bgcolor="red">
                  <tr>
                    <th class="titleMode" onmouseover="this.className='highlightTitleMode clickable';"
                                        onmouseout="this.className='titleMode clickable';"
                                        onclick="toggle_visibility_by_id('GlobalXXXNotification','plusminusGlobalXXXNotification')">
                      Global Fatal and Error &#160;  
                      <img src="Data\Plus.gif" class="clickable" id="plusminusGlobalXXXNotification">
                        <xsl:attribute name="height"><xsl:copy-of select="$iconHSize" /></xsl:attribute>
                      </img>

                    </th>
                  </tr>

                  <tr>
                    <td>
                      <span id="GlobalXXXNotification" class="displayHide">
                        <!-- 3.1- Display list of Data source -->
                        <dd>
                          <table border="1" width="100%" cellpadding="1" cellspacing="0">
                            <!-- table NOTIFICATON -->
                            <xsl:apply-templates select="./Notification"/>
                          </table>
                        </dd>
                      </span>
                    </td>
                  </tr>
                </table>
              </xsl:if>

              <xsl:if test="$ErrorMode = 2">
                <table xclass="frame" width="100%" bgcolor="red">
        <tr>
          <th class="titleMode" onmouseover="this.className='highlightTitleMode clickable';"
                              onmouseout="this.className='titleMode clickable';"
                              onclick="toggle_visibility_by_id('ObjectNotification','plusminusObjectNotification')">
            <xsl:value-of select="./Set[@Name='Resource']/Metric[@Name='ErrorOnObjects']/@nls"/>&#160;
            <img src="Data\Plus.gif" class="clickable" id="plusminusObjectNotification">
                <xsl:attribute name="height"><xsl:copy-of select="$iconHSize" /></xsl:attribute>
              </img>

          </th>
        </tr>

        <tr>
          <td>
            <span id="ObjectNotification" class="displayHide">
              <!-- 3.1- Display list of Data source -->
              <dd>



                  <!-- table OBJECT-NOTIFICATON-SUMMARY -->

                  <xsl:if test="$ErrorType =2 ">
                    <xsl:apply-templates select="./Set/Object/Notification[@Sev='Fatal']"/>
                  </xsl:if>
                  <xsl:if test="$ErrorType =12 ">
                    <xsl:apply-templates select="./Set/Object/Notification[@Sev='Error']"/>
                  </xsl:if>
                  <xsl:if test="$ErrorType =3 ">
                    <xsl:apply-templates select="./Set/Object/Engine/Notification[@Sev='Fatal']"/>
                  </xsl:if>
                  <xsl:if test="$ErrorType =13 ">
                    <xsl:apply-templates select="./Set/Object/Engine/Notification[@Sev='Error']"/>
                  </xsl:if>
                  <xsl:if test="$ErrorType =4 ">
                    <xsl:apply-templates select="./Set/Notification[@Sev='Fatal']"/>
                  </xsl:if>
                  <xsl:if test="$ErrorType =14 ">
                    <xsl:apply-templates select="./Set/Notification[@Sev='Error']"/>
                  </xsl:if>

              </dd>
            </span>
          </td>
        </tr>
      </table>
            </xsl:if>
    </th>
    </tr>
    </table>
        </td>
      </tr>

    </xsl:if>

    <!-- DISPLAY Warning panel -->
    <xsl:if test="$ErrorType = -1">

      <!-- Return the main return Code -->
      <tr>
        <td>
          <!--          ErrorType=<xsl:copy-of select="$ErrorType" /> - ErrorMode=<xsl:copy-of select="$ErrorMode" /> -->
          <table class="frame" width="100%" bgcolor="white">
            <tr>
              <!-- Display the main return Code icon if any - else display the default  -->
              <!--            <th class="titleMode" WIDTH="20" VALIGN="top">
              <IMG ALIGN="LEFT" HEIGHT="45">
                  <xsl:attribute name="SRC"><xsl:copy-of select="$GlobalReturnCodeIcon" /></xsl:attribute>            
                  <xsl:attribute name="alt"><xsl:copy-of select="$GlobalReturnCodeIcon" /></xsl:attribute>            
              </IMG>
          </th>
 -->
              <th>
                <table xclass="frame" width="100%" bgcolor="White">
                  <tr>
                    <th class="titleMode">
                      <xsl:value-of select="./Set[@Name='GlobalInformation']/Set[@Name='ExecutionMetrics']/Metric[@Name='GlobalReturnCode']/@nls"/>
                      =
                      <xsl:value-of select="./Set[@Name='GlobalInformation']/Set[@Name='ExecutionMetrics']/Metric[@Name='GlobalReturnCode']/@value"/>
                    </th>
                  </tr>
                </table>


                <xsl:if test="$ErrorMode = -1">
                  <table xclass="frame" width="100%" bgcolor="white">
                    <tr>
                      <th class="titleMode" onmouseover="this.className='highlightTitleMode clickable';"
                                          onmouseout="this.className='titleMode clickable';"
                                          onclick="toggle_visibility_by_id('GlobalXXXNotification','plusminusGlobalXXXNotification')">
                        Global Warning  &#160;
                        <img src="Data\Plus.gif" class="clickable" id="plusminusGlobalXXXNotification">
                          <xsl:attribute name="height">
                            <xsl:copy-of select="$iconHSize" />
                          </xsl:attribute>
                        </img>

                      </th>
                    </tr>

                    <tr>
                      <td>
                        <span id="GlobalXXXNotification" class="displayHide">
                          <!-- 3.1- Display list of Data source -->
                          <dd>
                            <table border="1" width="100%" cellpadding="1" cellspacing="0">
                              <!-- table NOTIFICATON -->
                              <xsl:apply-templates select="./Notification"/>
                            </table>
                          </dd>
                        </span>
                      </td>
                    </tr>
                  </table>
                </xsl:if>
              </th>
            </tr>
          </table>
        </td>
      </tr>

    </xsl:if>
  </xsl:template>

<!-- DISPLAY THE NOTIFICATION UNDER THE GLOBAL NODE -->
  
<!-- DISPLAY THE NOTIFICATION UNDER AN OBJECT NODE -->
  <xsl:template name="HeaderDisplayObjectNotifications">
        <td valign="top"><b><xsl:value-of select="@Sev"/></b></td>
        <td valign="top"><b><xsl:value-of select="@Name"/></b></td>
        <xsl:call-template name="HeaderDisplayLongHelp"/> <!-- include Infra_xsl_HeaderNotifications.xsl -->
  </xsl:template>

<!-- DISPLAY THE NOTIFICATION UNDER THE MAIN OBJECT SET NODE -->
  <xsl:template name="HeaderObjectSetNotification">
    <!-- OBJECT_SET NOTIFICATION DISPLAY -->
    <xsl:if test="count(Set[@Name='ObjectSet']/Notification)!=0">
           <tr>
             <td>
               <table class="frame" xwidth="100%">
          <xsl:for-each select="Set[@Name='ObjectSet']/Notification">
             <xsl:if test="@Sev='Error' or @Sev='Fatal'">
                <tr><xsl:attribute name="bgcolor"><xsl:copy-of select="$COLORError" /></xsl:attribute>
               <td colspan="1" valign="top" width="10%"> <xsl:value-of select="@Sev"/></td>
               <td colspan="1" valign="top" width="10%"> <xsl:value-of select="@Name"/> </td>
                <xsl:call-template name="HeaderDisplayLongHelp"/> <!-- include Infra_xsl_HeaderNotifications.xsl -->

                </tr>
            </xsl:if>
               <xsl:if test="@Sev='Warning'">
                <tr><xsl:attribute name="bgcolor"><xsl:copy-of select="$COLORWarning" /></xsl:attribute>
                <td colspan="1" valign="top" width="10%"> <xsl:value-of select="@Sev"/> </td>
                <td colspan="1" valign="top" width="10%"> <xsl:value-of select="@Name"/> </td>
                <xsl:call-template name="HeaderDisplayLongHelp"/> <!-- include Infra_xsl_HeaderNotifications.xsl -->
                </tr>
            </xsl:if>
            <xsl:if test="@Sev='Info' or @Sev='Debug' or @Sev='Trace'">
                <tr bgcolor="#FFFFFF">
                <td colspan="1" valign="top" width="10%"> <xsl:value-of select="@Sev"/> </td>
               <td colspan="1" valign="top" width="10%"> <xsl:value-of select="@Name"/> </td>
                <td colspan="2" valign="top" xwidth="10%"> <xsl:value-of select="@msg"/> </td>
              </tr>
            </xsl:if>
          </xsl:for-each>
               </table>
             </td>
           </tr>
        </xsl:if>
    <!-- OBJECT_SET NOTIFICATION DISPLAY -->
  </xsl:template>
 

  <!-- DISPLAY THE LONGHELP ATTACHED TO ANY FATAL/ERROR/WARNING -->
  <xsl:template name="HeaderDisplayLongHelp">
          <xsl:choose>
            <xsl:when test="count(Metric[@Name='LongHelp'])!=0">
              <xsl:variable name="NOTIFTITLE"><xsl:value-of select="@msg"/></xsl:variable>
              <xsl:variable name="NOTIFSECTIONID">NOTIF_HEADERSECTIONID_<xsl:value-of select="@Id"/></xsl:variable>
              <td valign="top" class="titleMode" onmouseover="this.className='highlightTitleMode clickable';" onmouseout="this.className='titleMode clickable';">
                  <xsl:attribute name="onclick">toggle_visibility_by_id('<xsl:copy-of select="$NOTIFSECTIONID"/>','plusminus<xsl:copy-of select="$NOTIFSECTIONID"/>')</xsl:attribute>
                  <xsl:copy-of select="$NOTIFTITLE" /> &#160; 
                  <img src="Data\Plus.gif" class="clickable">
                    <xsl:attribute name="height"><xsl:copy-of select="$iconHSize" /></xsl:attribute>
                    <xsl:attribute name="id">plusminus<xsl:copy-of select="$NOTIFSECTIONID"/></xsl:attribute>
                  </img>
                    <span class="displayHide">
                    <xsl:attribute name="id"><xsl:value-of select="$NOTIFSECTIONID"/></xsl:attribute>
                      <p>
                        <xsl:for-each select="Metric[@Name='LongHelp']">
                          <dd><xsl:if test="string-length(@value)&gt;0"><xsl:value-of select="@value"/>  :</xsl:if> <xsl:value-of select="@nls"/></dd>
                        </xsl:for-each>
                      </p>
                    </span>
              </td>
            </xsl:when>
            <xsl:otherwise>
              <td valign="top"><xsl:value-of select="@msg"/></td>
              </xsl:otherwise>
  </xsl:choose>
 </xsl:template>

</xsl:stylesheet>
