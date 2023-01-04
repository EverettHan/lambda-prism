<?xml version="1.0" encoding="UTF-8"?>
<!-- WARNING: YWE 15:07:06 SINGLE-CODE 2013x => NO LOCAL CHANGE EXPECTED - USE IMPORT -->
<xsl:stylesheet version="2.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform" xmlns:fo="http://www.w3.org/1999/XSL/Format" xmlns:xs="http://www.w3.org/2001/XMLSchema" xmlns:fn="http://www.w3.org/2005/02/xpath-functions" xmlns:xdt="http://www.w3.org/2005/02/xpath-datatypes">
<xsl:output method="html" indent="yes" encoding="UTF-8"/>

  <xsl:variable name="COLORNotifFatal">#FF0000</xsl:variable>
  <xsl:variable name="COLORNotifError">#FF9900</xsl:variable>
  <xsl:variable name="COLORNotifWarning">#CCFF00</xsl:variable>
  <xsl:variable name="COLORNotifDefault"></xsl:variable>

  <!-- ============================================= -->
  <!--  Notification template                        -->
  <!-- ============================================= -->



<!-- DISPLAY THE NOTIFICATION UNDER THE GLOBAL NODE -->
  <xsl:template name="DisplayGlobalNotifications">
        <td valign="top" width="10%"><b><xsl:value-of select="@Sev"/></b></td>
        <td valign="top" width="15%"><b><xsl:value-of select="@Name"/></b></td>
        <xsl:call-template name="DisplayLongHelp"/> <!-- include Infra_Xsl_Notifications.xsl -->
  </xsl:template>

<!-- DISPLAY THE NOTIFICATION UNDER AN OBJECT NODE -->
  <xsl:template name="DisplayObjectNotifications">
        <td valign="top"><b><xsl:value-of select="@Sev"/></b></td>
        <td valign="top"><b><xsl:value-of select="@Name"/></b></td>
        <xsl:call-template name="DisplayLongHelp"/> <!-- include Infra_Xsl_Notifications.xsl -->
  </xsl:template>

<!-- DISPLAY THE NOTIFICATION UNDER THE MAIN OBJECT SET NODE -->
  <xsl:template name="ObjectSetNotification">
    <!-- OBJECT_SET NOTIFICATION DISPLAY -->
    <xsl:if test="count(Set[@Name='ObjectSet']/Notification)!=0">
           <tr>
             <td>
               <table class="frame" xwidth="100%">
          <xsl:for-each select="Set[@Name='ObjectSet']/Notification">
             <xsl:if test="@Sev='Error' or @Sev='Fatal'">
                <tr><xsl:attribute name="bgcolor"><xsl:copy-of select="$COLORNotifError" /></xsl:attribute>
               <td colspan="1" valign="top" width="10%"> <xsl:value-of select="@Sev"/></td>
               <td colspan="1" valign="top" width="10%"> <xsl:value-of select="@Name"/> </td>
                <xsl:call-template name="DisplayLongHelp"/> <!-- include Infra_Xsl_Notifications.xsl -->

                </tr>
            </xsl:if>
               <xsl:if test="@Sev='Warning'">
                <tr><xsl:attribute name="bgcolor"><xsl:copy-of select="$COLORNotifWarning" /></xsl:attribute>
                <td colspan="1" valign="top" width="10%"> <xsl:value-of select="@Sev"/> </td>
                <td colspan="1" valign="top" width="10%"> <xsl:value-of select="@Name"/> </td>
                <xsl:call-template name="DisplayLongHelp"/> <!-- include Infra_Xsl_Notifications.xsl -->
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
  <xsl:template name="DisplayLongHelp">
          <xsl:choose>
            <xsl:when test="count(Metric[@Name='LongHelp'])!=0">
              <xsl:variable name="NOTIFTITLE"><xsl:value-of select="@msg"/></xsl:variable>
              <xsl:variable name="NOTIFSECTIONID">NOTIF_ObjectSECTIONID_<xsl:value-of select="@Id"/></xsl:variable>
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
                          <dd>
                            <xsl:if test="string-length(@value)&gt;0">
                              <xsl:value-of select="@value"/>  :
                            </xsl:if>
                            <xsl:value-of select="@nls"/>
                          </dd>
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
