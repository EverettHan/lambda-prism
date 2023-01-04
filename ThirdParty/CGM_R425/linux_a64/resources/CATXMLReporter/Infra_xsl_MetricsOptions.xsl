<?xml version="1.0" encoding="UTF-8"?>
<!-- WARNING: YWE 15:07:06 SINGLE-CODE 2013x => NO LOCAL CHANGE EXPECTED - USE IMPORT -->
<xsl:stylesheet version="2.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform" xmlns:fo="http://www.w3.org/1999/XSL/Format" xmlns:xs="http://www.w3.org/2001/XMLSchema" xmlns:fn="http://www.w3.org/2005/02/xpath-functions" xmlns:xdt="http://www.w3.org/2005/02/xpath-datatypes">
<xsl:output method="html" indent="yes" encoding="UTF-8"/>
  <xsl:variable name="MetricsOptions">
    <xsl:value-of select="Execution/Set[@Name='Resource']/Metric[@Name='MetricsOptions']/@nls"/>
  </xsl:variable>
  <xsl:variable name="Metrics">
    <xsl:value-of select="Execution/Set[@Name='Resource']/Metric[@Name='Metrics']/@nls"/>
  </xsl:variable>
  <xsl:variable name="Options">
    <xsl:value-of select="Execution/Set[@Name='Resource']/Metric[@Name='Options']/@nls"/>
  </xsl:variable>
  <xsl:variable name="ExchangeChannel">
    <xsl:value-of select="Execution/Set[@Name='Resource']/Metric[@Name='ExchangeChannel']/@nls"/>
  </xsl:variable>
  <xsl:variable name="EnvironmentVariables">
    <xsl:value-of select="Execution/Set[@Name='Resource']/Metric[@Name='EnvironmentVariables']/@nls"/>
  </xsl:variable>

  <xsl:template name="InfraMetricOptions">

    <!-- =============================== -->
  <!-- ====================================================== -->
  <!--   3-2 Display list of Metric and Options if almost one -->
  <!-- ====================================================== -->
  <xsl:if test="count(.//Metric)!=0 or count(.//Option)!=0 ">
   <tr>
      <td>
        <table class="frame" border="0" width="100%">
          <!-- TABLE M-->
          <tr>
            <th class="titleMode" onmouseover="this.className='highlightTitleMode clickable';"
                                onmouseout="this.className='titleMode clickable';"
                                onclick="toggle_visibility_by_id('MetricsOption','plusminusMetricsOption')">

              <xsl:value-of select="$MetricsOptions"/>&#160;
              <img src="Data\Plus.gif" class="clickable" id="plusminusMetricsOption">
                <xsl:attribute name="height"><xsl:copy-of select="$iconHSize" /></xsl:attribute>
              </img>

            </th>
          </tr>
          <tr>
            <td>
              <span id="MetricsOption" class="displayHide">
                <!-- 3.2- Display list of Metrics and Options -->
                <dd>
                  <table border="0" WIDTH="95%">
                    <!-- Display Metrics -->
                    <xsl:if test="count(.//Set[@Name='ExecutionMetrics']/Metric)!=0 ">
                      <!-- METRICS SECTION ============================================ DEB -->
                      <!-- METRICS SECTION ============================================ DEB -->
                      <!-- METRICS SECTION ============================================ DEB -->
                      <tr>
                        <td colspan="2">
                          <table class="frame" width="100%">
                            <tr>
                              <th class="titleMode" onmouseover="this.className='highlightTitleMode clickable';" onmouseout="this.className='titleMode clickable';">
                                <xsl:attribute name="onclick">toggle_visibility_by_id('ExecutionMetrics','plusminusExecutionMetrics')</xsl:attribute>
                                <xsl:value-of select="$Metrics"/>&#160;
                                <img src="Data\Plus.gif" class="clickable">
                                  <xsl:attribute name="height"><xsl:copy-of select="$iconHSize" /></xsl:attribute>
                                  <xsl:attribute name="id">plusminusExecutionMetrics</xsl:attribute>
                                </img>
                              </th>
                            </tr>
                            <tr>
                              <td >
                                <span id="ExecutionMetrics" class="displayHide">
                                  <xsl:call-template name="ExecutionMetrics"/>
                                </span>
                              </td>
                            </tr>
                          </table>
                        </td>
                      </tr>
                      <!-- METRICS SECTION ============================================ END -->
                      <!-- METRICS SECTION ============================================ END -->
                      <!-- METRICS SECTION ============================================ END -->
                    </xsl:if>

                    <!-- Display Execution Options -->
                    <xsl:if test="count(.//Set[@Name='ExecutionOption']/Option)!=0 ">
                      <!-- EXECUTION-OPTIONS SECTION ============================================ DEB -->
                      <!-- EXECUTION-OPTIONS SECTION ============================================ DEB -->
                      <!-- EXECUTION-OPTIONS SECTION ============================================ DEB -->
                      <tr>
                        <td colspan="2">
                          <table class="frame" width="100%">
                            <tr>
                              <th class="titleMode" onmouseover="this.className='highlightTitleMode clickable';" onmouseout="this.className='titleMode clickable';">
                                <xsl:attribute name="onclick">toggle_visibility_by_id('ExecutionOption','plusminusExecutionOption')</xsl:attribute>
                                <xsl:value-of select="$Options"/>&#160;
                                <img src="Data\Plus.gif" class="clickable">
                                  <xsl:attribute name="height"><xsl:copy-of select="$iconHSize" /></xsl:attribute>
                                  <xsl:attribute name="id">plusminusExecutionOption</xsl:attribute>
                                </img>
                              </th>
                            </tr>
                            <tr>
                              <td >
                                <span id="ExecutionOption" class="displayHide">
                                  <xsl:call-template name="temp_ExecutionOption"/>
                                </span>
                              </td>
                            </tr>
                          </table>
                        </td>
                      </tr>
                      <!-- EXECUTION-OPTIONS SECTION ============================================ END -->
                      <!-- EXECUTION-OPTIONS SECTION ============================================ END -->
                      <!-- EXECUTION-OPTIONS SECTION ============================================ END -->
                    </xsl:if>

                    <!-- Display Execution Options -->
                    <xsl:if test="count(.//Set[@Name='ExchangeChannelOption']/Option)!=0 ">
                      <!-- EXCHANGECHANNEL-OPTIONS SECTION ============================================ DEB -->
                      <!-- EXCHANGECHANNEL-OPTIONS SECTION ============================================ DEB -->
                      <!-- EXCHANGECHANNEL-OPTIONS SECTION ============================================ DEB -->
                      <tr>
                        <td colspan="2">
                          <table class="frame" width="100%">
                            <tr>
                              <th class="titleMode" onmouseover="this.className='highlightTitleMode clickable';" onmouseout="this.className='titleMode clickable';">
                                <xsl:attribute name="onclick">toggle_visibility_by_id('ExchangeChannelOption','plusminusExchangeChannelOption')</xsl:attribute>
                                <xsl:value-of select="$ExchangeChannel"/>&#160;
                                <img src="Data\Plus.gif" class="clickable">
                                  <xsl:attribute name="height">
                                    <xsl:copy-of select="$iconHSize" />
                                  </xsl:attribute>
                                  <xsl:attribute name="id">plusminusExchangeChannelOption</xsl:attribute>
                                </img>
                              </th>
                            </tr>
                            <tr>
                              <td >
                                <span id="ExchangeChannelOption" class="displayHide">
                                  <xsl:call-template name="temp_ExchangeChannelOption"/>
                                </span>
                              </td>
                            </tr>
                          </table>
                        </td>
                      </tr>
                      <!-- EXCHANGECHANNEL-OPTIONS SECTION ============================================ END -->
                      <!-- EXCHANGECHANNEL-OPTIONS SECTION ============================================ END -->
                      <!-- EXCHANGECHANNEL-OPTIONS SECTION ============================================ END -->
                    </xsl:if>
                    <!-- Display Environment Variable -->
                    <xsl:if test="count(.//Set[@Name='EnvironmentVariable']/Option)!=0 ">
                      <!-- ENVVAR SECTION ============================================ DEB -->
                      <!-- ENVVAR SECTION ============================================ DEB -->
                      <!-- ENVVAR SECTION ============================================ DEB -->
                      <tr>
                        <td colspan="2">
                          <table class="frame" width="100%">
                            <tr>
                              <th class="titleMode" onmouseover="this.className='highlightTitleMode clickable';" onmouseout="this.className='titleMode clickable';">
                                <xsl:attribute name="onclick">toggle_visibility_by_id('EnvironmentVariable','plusminusEnvironmentVariable')</xsl:attribute>
                                <xsl:value-of select="$EnvironmentVariables"/>&#160;
                                <img src="Data\Plus.gif" class="clickable">
                                  <xsl:attribute name="height"><xsl:copy-of select="$iconHSize" /></xsl:attribute>
                                  <xsl:attribute name="id">plusminusEnvironmentVariable</xsl:attribute>
                                </img>
                              </th>
                            </tr>
                            <tr>
                              <td >
                                <span id="EnvironmentVariable" class="displayHide">
                                  <xsl:call-template name="EnvironmentVariable"/>
                                </span>
                              </td>
                            </tr>
                          </table>
                        </td>
                      </tr>
                      <!-- ENVVAR SECTION ============================================ END -->
                      <!-- ENVVAR SECTION ============================================ END -->
                      <!-- ENVVAR SECTION ============================================ END -->
                    </xsl:if>

                  </table>
                </dd>
              </span>
            </td>
          </tr>
        </table>
        <!-- END of Option/Metrics display -->
      </td>
    </tr>
  </xsl:if>
  </xsl:template>

  <!-- ====================================================== -->
  <!--         INTERNAL TEMPLATE DEFINITION                   -->
  <!-- ====================================================== -->
  <xsl:template name="temp_ExecutionOption">
    <!-- EXECUTION-OPTIONS TEMPLATE ============================================ DEB -->
    <!-- EXECUTION-OPTIONS TEMPLATE ============================================ DEB -->
    <!-- EXECUTION-OPTIONS TEMPLATE ============================================ DEB -->
    <table border="1" cellspacing="1" cellpadding="3" align="right" class="objectFBDITable">
      <th class = "defaultMode" width="375"><xsl:copy-of select="$NameColumn" /></th>
      <th class = "defaultMode" width="575"><xsl:copy-of select="$ValueColumn" /></th>
      <xsl:for-each select="Set/Set[@Name = 'ExecutionOption']/Option">
        <tr>
          <td class="defaultMode">
            <xsl:value-of select="@nls"/>
          </td>
          <xsl:choose>
            <xsl:when test="@isSet='T'">
              <td class="defaultMode">
                <xsl:value-of select="@value"/>
              </td>
            </xsl:when>
            <xsl:otherwise>
              <td>
                <i>No value set</i>
              </td>
            </xsl:otherwise>
          </xsl:choose>
        </tr>
      </xsl:for-each>
    </table>
    <!-- EXECUTION-OPTIONS TEMPLATE ============================================ DEB -->
    <!-- EXECUTION-OPTIONS TEMPLATE ============================================ DEB -->
    <!-- EXECUTION-OPTIONS TEMPLATE ============================================ DEB -->
  </xsl:template>
  
    <xsl:template name="temp_ExchangeChannelOption">
    <!-- EXCHANGECHANNEL-OPTIONS TEMPLATE ============================================ DEB -->
    <!-- EXCHANGECHANNEL-OPTIONS TEMPLATE ============================================ DEB -->
    <!-- EXCHANGECHANNEL-OPTIONS TEMPLATE ============================================ DEB -->
    <table border="1" cellspacing="1" cellpadding="3" align="right" class="objectFBDITable">
      <th class = "defaultMode" width="375"><xsl:copy-of select="$NameColumn" /></th>
      <th class = "defaultMode" width="575"><xsl:copy-of select="$ValueColumn" /></th>
      <xsl:for-each select="Set/Set[@Name = 'ExchangeChannelOption']/Option">
        <tr>
          <td class="defaultMode">
            <xsl:value-of select="@nls"/>
          </td>
          <xsl:choose>
            <xsl:when test="@isSet='T'">
              <td class="defaultMode">
                <xsl:value-of select="@value"/>
              </td>
            </xsl:when>
            <xsl:otherwise>
              <td>
                <i>No value set</i>
              </td>
            </xsl:otherwise>
          </xsl:choose>
        </tr>
      </xsl:for-each>
    </table>
    <!-- EXCHANGECHANNEL-OPTIONS TEMPLATE ============================================ DEB -->
    <!-- EXCHANGECHANNEL-OPTIONS TEMPLATE ============================================ DEB -->
    <!-- EXCHANGECHANNEL-OPTIONS TEMPLATE ============================================ DEB -->
  </xsl:template>
  <!-- Template: Environment Variable -->
  <xsl:template name="EnvironmentVariable">
    <!-- ENVVAR TEMPLATE ============================================ DEB -->
    <!-- ENVVAR TEMPLATE ============================================ DEB -->
    <!-- ENVVAR TEMPLATE ============================================ DEB -->
    <table border="1" cellspacing="1" cellpadding="3" align="right" class="objectFBDITable">
      <th class = "defaultMode" width="375"><xsl:copy-of select="$NameColumn" /></th>
      <th class = "defaultMode" width="575"><xsl:copy-of select="$ValueColumn" /></th>
      <xsl:for-each select="Set/Set[@Name='EnvironmentVariable']/Option[@filtering='Public']">
        <tr>
          <td class="defaultMode">
            <xsl:value-of select="@Name"/>
          </td>
          <xsl:choose>
            <xsl:when test="@isSet='T'">
              <td class="defaultMode">
                [<xsl:value-of select="@value"/>]=<xsl:value-of select="@nls"/>
              </td>
            </xsl:when>
            <xsl:otherwise>
              <td>
                <i>No value set</i>
              </td>
            </xsl:otherwise>
          </xsl:choose>
        </tr>
      </xsl:for-each>
      <xsl:for-each select="Set/Set[@Name='EnvironmentVariable']/Option[@filtering='Limited']">
        <tr>
          <td class="defaultMode">
            <xsl:value-of select="@Name"/>
          </td>
          <xsl:choose>
            <xsl:when test="@isSet='T'">
              <td bgcolor="yellow">
                [<xsl:value-of select="@value"/>]=<xsl:value-of select="@nls"/> - Limited Availability
              </td>
            </xsl:when>
            <xsl:otherwise>
              <td>
                <i>No value set</i>
              </td>
            </xsl:otherwise>
          </xsl:choose>
        </tr>
      </xsl:for-each>
      <xsl:for-each select="Set/Set[@Name='EnvironmentVariable']/Option[@filtering='Restricted']">
        <tr>
          <td class="defaultMode">
            <xsl:value-of select="@Name"/>
          </td>
          <xsl:choose>
            <xsl:when test="@isSet='T'">
              <td bgcolor="yellow">
                [<xsl:value-of select="@value"/>]=<xsl:value-of select="@nls"/> - Restricted Availability
              </td>
            </xsl:when>
            <xsl:otherwise>
              <td>
                <i>No value set</i>
              </td>
            </xsl:otherwise>
          </xsl:choose>
        </tr>
      </xsl:for-each>
      <xsl:for-each select="Set/Set[@Name='EnvironmentVariable']/Option[@filtering='InternalDS']">
        <tr>
          <td class="defaultMode">
            <xsl:value-of select="@Name"/>
          </td>
          <xsl:choose>
            <xsl:when test="@isSet='T'">
              <td bgcolor="orange">
                [<xsl:value-of select="@value"/>]=<xsl:value-of select="@nls"/> - Internal Dassault Systemes
              </td>
            </xsl:when>
            <xsl:otherwise>
              <td>
                <i>No value set</i>
              </td>
            </xsl:otherwise>
          </xsl:choose>
        </tr>
      </xsl:for-each>
    </table>
    <!-- ENVVAR TEMPLATE ============================================ END -->
    <!-- ENVVAR TEMPLATE ============================================ END -->
    <!-- ENVVAR TEMPLATE ============================================ END -->
  </xsl:template>
  <!-- Template: Metrics -->
  <xsl:template name="ExecutionMetrics">
    <!-- METRIC TEMPLATE ============================================ DEB -->
    <!-- METRIC TEMPLATE ============================================ DEB -->
    <!-- METRIC TEMPLATE ============================================ DEB -->
    <table border="1" cellspacing="1" cellpadding="3" align="right" class="objectFBDITable">
      <th class = "defaultMode" width="375"><xsl:copy-of select="$NameColumn" /></th>
      <th class = "defaultMode" width="575"><xsl:copy-of select="$ValueColumn" /></th>
      <xsl:for-each select="Set/Set[@Name = 'ExecutionMetrics']/Metric">
        <tr>
          <td class="defaultMode">
            <xsl:value-of select="@nls"/>
          </td>
          <xsl:choose>
            <xsl:when test="@isSet='T'">
              <td class="defaultMode">
                <xsl:value-of select="@value"/>
              </td>
            </xsl:when>
            <xsl:otherwise>
              <td>
                <i>No value set</i>
              </td>
            </xsl:otherwise>
          </xsl:choose>
        </tr>
      </xsl:for-each>
    </table>
    <!-- METRIC TEMPLATE ============================================ END -->
    <!-- METRIC TEMPLATE ============================================ END -->
    <!-- METRIC TEMPLATE ============================================ END -->
  </xsl:template>
  <!-- Template: Execution Options -->

  
 
   
</xsl:stylesheet>
