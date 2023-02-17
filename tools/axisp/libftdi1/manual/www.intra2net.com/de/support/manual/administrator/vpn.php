<!DOCTYPE html>
    <html><head>
      <meta http-equiv="Content-Type" content="text/html; charset=utf-8">
   <title>VPN | Administrator Handbuch
  </title>
      <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <link rel="stylesheet" type="text/css" media="screen" href="../../../screen.css">
    <link rel="stylesheet" type="text/css" media="print" href="../../../print.css">
    <meta name="generator" content="DocBook XSL Stylesheets V1.74.3"><link rel="home" href="index.php" title="Intra2net Administrator Handbuch"><link rel="up" href="index.php" title="Intra2net Administrator Handbuch"><link rel="prev" href="firewall-examples-dmz.php" title="37.5. Aufgabe 5: Webserver in der DMZ"><link rel="next" href="vpn-basics.php" title="38. Kapitel - IPSec Grundlagen">
    <meta http-equiv="content-language" content="de">
  </head><body>
          
    <!-- header start -->

<div id="header">

<div id="logo">
	<a href="../../../index.html">
		<div id="logo_screen"><img src="../../../pictures/intra2net.gif" alt="Intra2net AG"></div>
		<div id="logo_print"><img src="../../../pictures/intra2net_print.gif" alt="Intra2net AG"></div>
	</a>
</div>

<div id="search">
	<form name="formsearch" method="get" action="http://www.intra2net.com/search/search.cgi">
		<input type="text" name="q" maxlength="64" id="searchinput" value="">
		<input type="image" name="submit" src="../../../pictures/search.gif" alt="Suche">
	</form>
</div>


<nav id="navigation">

<a href="vpn.php#navigation"><div class="mobilemenu"><img src="../../../pictures/mobile_icon.gif" alt="Navigation"></div></a>
<a href="vpn.php#"><div class="mobilemenu"><img src="../../../pictures/mobile_icon.gif" alt="Navigation"></div></a>

<ul class="navbar">

<li id="Produkte"><a href="../../../../en/products/index.html">Produkte</a>
	<div class="dropdown">
		<div class="navgrid">
			<div class="navgrid-unit navcol1_of_3">
				<h4>SOFTWARE</h4>
					<ul class="navmenu">
						<li><a href="../../../produkte/index.php">&Uuml;bersicht</a></li>
						<li><a href="../../../produkte/intranator.php">Business Server</a></li>
						<li><a href="../../../produkte/security_gateway.php">Security Gateway</a></li>
						<li><a href="../../../produkte/network_security.php">Network Security</a></li>
						<li><a href="../../../produkte/lizenzen/index.php">Lizenzbestimmungen</a></li>
					</ul>
			</div>
			<div class="navgrid-unit navcol1_of_3">
				<h4>HARDWARE</h4>
					<ul class="navmenu">
						<li><a href="../../../produkte/hardware.php">&Uuml;bersicht</a></li>
						<li><a href="../../../produkte/appliance_eco.php">Appliance Eco</a></li>
						<li><a href="../../../produkte/appliance_pro.php">Appliance Pro</a></li>
						<li><a href="../../../produkte/appliance_ultimate.php">Appliance Ultimate</a></li>
					</ul>
			</div>
			<div class="navgrid-unit navcol1_of_3">
				<h4>REFERENZEN</h4>
					<ul class="navmenu">
						<li><a href="../../../produkte/anwenderberichte.php">Anwenderberichte</a></li>
						<li><a href="../../../produkte/kundenstimmen.php">Kundenstimmen</a></li>
						<li><a href="../../../produkte/pressestimmen.php">Pressestimmen</a></li>
					</ul>
			</div>
		</div> <!-- close .grid div -->
	</div> <!-- close .dropdown div -->
</li>

<li id="Download"><a href="../../../download.1">Download</a>
	<div class="dropdown">
		<ul>
			<li><a href="../../../download/index.php">Software</a></li>
			<li><a href="../../../download/datenblaetter.php">Datenbl&auml;tter</a></li>
			<li><a href="../../../download/handbuecher.php">Handb&uuml;cher</a></li>
		</ul>
	</div>
</li>

<li id="Support" class="selected"><a href="../../../../en/support/index.html">Support</a>
	<div class="dropdown">
		<ul>
			<li><a href="../../anfrage.php">Support-Anfrage</a></li>
			<li><a href="../../handbuecher.php">Handb&uuml;cher</a></li>
			<li><a href="http://forum.intra2net.com/">Forum</a></li>
			<li><a href="../../unterstuetzte_hardware.php">Unterst&uuml;tzte Hardware</a></li>
			<li><a href="../../antispam/index.html">Blacklist Performance</a></li>
			<li><a href="../../schulung.php">Schulung</a></li>
			<li><a href="../../fernwartung.php">Fernwartung</a></li>
		</ul>
	</div>
</li>

<li id="Kaufen"><a href="../../../kaufen/index.html">Kaufen</a>
	<div class="dropdown">
		<ul>
			<li><a href="../../../kaufen/index.php">Partner finden</a></li>
			<li><a href="../../../partner-werden">Partner werden</a></li>
			<li><a href="http://partner.intra2net.com/">Partnerweb</a></li>
		</ul>
	</div>
</li>

<li id="Unternehmen"><a href="../../../unternehmen/index.html">Unternehmen</a>
	<div class="dropdown">
		<ul>
			<li><a href="../../../unternehmen/index.php">&Uuml;ber Intra2net</a></li>
			<li><a href="../../../unternehmen/presse/index.php">Presse</a></li>
			<li><a href="../../../unternehmen/karriere.php">Karriere</a></li>
			<li><a href="../../../unternehmen/kontakt.php">Kontakt</a></li>
		</ul>
	</div>
</li>

</ul> <!-- close #navbar ul -->

</nav>

</div> <!-- close #header div -->


<div id="page">


<div id="content">

<!-- header end -->

    <div id="manual">
    <!-- content start -->

    <div class="navheader"><table width="100%" summary="Navigation header"><tr><th colspan="3" align="center">Teil&nbsp;6.&nbsp;VPN</th></tr><tr><td width="20%" align="left"><a accesskey="p" href="firewall-examples-dmz.php">Zur&uuml;ck</a>&nbsp;</td><th width="60%" align="center">&nbsp;</th><td width="20%" align="right">&nbsp;<a accesskey="n" href="vpn-basics.php">Weiter</a></td></tr></table><hr></div><div class="part" lang="de"><div class="titlepage"><div><div><h1 class="title"><a name="vpn"></a>Teil&nbsp;6.&nbsp;VPN</h1></div></div></div><div class="toc"><p><b>Inhaltsverzeichnis</b></p><dl><dt><span class="chapter"><a href="vpn-basics.php">38. IPSec Grundlagen</a></span></dt><dd><dl><dt><span class="sect1"><a href="vpn-basics.php#vpn-basics-ipsec">38.1. IPSec</a></span></dt><dt><span class="sect1"><a href="vpn-basics-public-key.php">38.2. Public-Key Kryptographie</a></span></dt><dt><span class="sect1"><a href="vpn-basics-certificates.php">38.3. Zertifikate</a></span></dt><dt><span class="sect1"><a href="vpn-basics-connections.php">38.4. IPSec Verbindungen</a></span></dt><dt><span class="sect1"><a href="vpn-basics-algorithms.php">38.5. Algorithmen</a></span></dt><dt><span class="sect1"><a href="vpn-basics-limitations.php">38.6. Einschr&auml;nkungen</a></span></dt><dt><span class="sect1"><a href="vpn-basics-compatibility.php">38.7. Kompatibilit&auml;t mit anderen IPSec-Gegenstellen</a></span></dt></dl></dd><dt><span class="chapter"><a href="vpn-keys.php">39. Schl&uuml;sselmanagement</a></span></dt><dd><dl><dt><span class="sect1"><a href="vpn-keys.php#vpn-keys-own">39.1. Eigene Schl&uuml;ssel</a></span></dt><dd><dl><dt><span class="sect2"><a href="vpn-keys.php#vpn-keys-own-ca">39.1.1. Zertifizierungsstellen (CAs)</a></span></dt></dl></dd><dt><span class="sect1"><a href="vpn-keys-foreign.php">39.2. Fremde Schl&uuml;ssel</a></span></dt></dl></dd><dt><span class="chapter"><a href="vpn-clients.php">40. Anbinden von einzelnen PCs</a></span></dt><dd><dl><dt><span class="sect1"><a href="vpn-clients.php#vpn-clients-concept">40.1. Konzept</a></span></dt><dt><span class="sect1"><a href="vpn-clients-intranator.php">40.2. Konfiguration auf dem Intranator</a></span></dt><dd><dl><dt><span class="sect2"><a href="vpn-clients-intranator.php#vpn-clients-intranator-prereq">40.2.1. Voraussetzungen</a></span></dt><dt><span class="sect2"><a href="vpn-clients-intranator.php#vpn-clients-intranator-basicconfig">40.2.2. Grundeinstellungen</a></span></dt><dt><span class="sect2"><a href="vpn-clients-intranator.php#vpn-clients-intranator-auth">40.2.3. Authentifizierung</a></span></dt><dt><span class="sect2"><a href="vpn-clients-intranator.php#vpn-clients-intranator-tunnel">40.2.4. Tunnel konfigurieren</a></span></dt><dt><span class="sect2"><a href="vpn-clients-intranator.php#vpn-clients-intranator-rights">40.2.5. Rechte</a></span></dt><dt><span class="sect2"><a href="vpn-clients-intranator.php#vpn-clients-intranator-activation">40.2.6. Aktivierung</a></span></dt></dl></dd></dl></dd><dt><span class="chapter"><a href="vpn-ncp-secure-entry.php">41. VPN mit dem NCP Secure Entry Client</a></span></dt><dd><dl><dt><span class="sect1"><a href="vpn-ncp-secure-entry.php#vpn-ncp-secure-entry-installation">41.1. Installation</a></span></dt><dt><span class="sect1"><a href="vpn-ncp-secure-entry-certificates.php">41.2. Zertifikate</a></span></dt><dt><span class="sect1"><a href="vpn-ncp-secure-entry-connection.php">41.3. Verbindungen</a></span></dt><dt><span class="sect1"><a href="vpn-ncp-secure-entry-intranator.php">41.4. Intranator</a></span></dt></dl></dd><dt><span class="chapter"><a href="vpn-shrew.php">42. VPN mit dem Shrew Soft VPN Client</a></span></dt><dd><dl><dt><span class="sect1"><a href="vpn-shrew.php#vpn-shrew-certificates">42.1. Zertifikate</a></span></dt><dt><span class="sect1"><a href="vpn-shrew-connection.php">42.2. Verbindung im Client konfigurieren</a></span></dt><dt><span class="sect1"><a href="vpn-shrew-intranator.php">42.3. Intranator</a></span></dt><dt><span class="sect1"><a href="vpn-shrew-connect.php">42.4. Verbindung aufbauen</a></span></dt><dt><span class="sect1"><a href="vpn-shrew-trace.php">42.5. Verbindungsprotokolle</a></span></dt></dl></dd><dt><span class="chapter"><a href="vpn-netgear-client.php">43. VPN mit dem NetGear ProSafe Client</a></span></dt><dd><dl><dt><span class="sect1"><a href="vpn-netgear-client.php#vpn-netgear-client-compatibility">43.1. Kompatibilit&auml;t</a></span></dt><dt><span class="sect1"><a href="vpn-netgear-client-installation.php">43.2. Installation</a></span></dt><dt><span class="sect1"><a href="vpn-netgear-client-certificates.php">43.3. Zertifikate</a></span></dt><dt><span class="sect1"><a href="vpn-netgear-client-connections.php">43.4. Verbindungen</a></span></dt><dt><span class="sect1"><a href="vpn-netgear-client-intranator.php">43.5. Intranator</a></span></dt></dl></dd><dt><span class="chapter"><a href="vpn-macosx.php">44. VPN mit Mac OS X</a></span></dt><dd><dl><dt><span class="sect1"><a href="vpn-macosx.php#vpn-macosx-installation">44.1. Installation</a></span></dt><dt><span class="sect1"><a href="vpn-macosx-cert-create.php">44.2. Zertifikate erzeugen</a></span></dt><dt><span class="sect1"><a href="vpn-macosx-cert-import.php">44.3. Zertifikate importieren</a></span></dt><dt><span class="sect1"><a href="vpn-macosx-connection.php">44.4. Verbindungen konfigurieren</a></span></dt><dt><span class="sect1"><a href="vpn-macosx-intranator.php">44.5. Intranator</a></span></dt></dl></dd><dt><span class="chapter"><a href="vpn-iphone.php">45. VPN mit dem Apple iPhone</a></span></dt><dd><dl><dt><span class="sect1"><a href="vpn-iphone.php#vpn-iphone-certificate-iphone">45.1. Zertifikat f&uuml;r das iPhone</a></span></dt><dt><span class="sect1"><a href="vpn-iphone-certificate-intranator.php">45.2. Zertifikat f&uuml;r den Intranator</a></span></dt><dt><span class="sect1"><a href="vpn-iphone-connection-intranator.php">45.3. Verbindung auf dem Intranator</a></span></dt><dt><span class="sect1"><a href="vpn-iphone-connection-iphone.php">45.4. Verbindung auf dem iPhone</a></span></dt></dl></dd><dt><span class="chapter"><a href="vpn-android-galaxys4.php">46. VPN mit Android</a></span></dt><dd><dl><dt><span class="sect1"><a href="vpn-android-galaxys4.php#vpn-android-prepare">46.1. Ger&auml;t vorbereiten</a></span></dt><dt><span class="sect1"><a href="vpn-android-certificates.php">46.2. Zertifikate</a></span></dt><dt><span class="sect1"><a href="vpn-android-galaxys4-connection-intranator.php">46.3. Verbindung auf dem Intranator</a></span></dt><dt><span class="sect1"><a href="vpn-android-galaxys4-connection-android.php">46.4. Verbindung auf Android</a></span></dt><dt><span class="sect1"><a href="vpn-android-galaxys4-simplify-menu.php">46.5. Verbindundsaufbau vereinfachen</a></span></dt><dt><span class="sect1"><a href="vpn-android-galaxys4-trace.php">46.6. Verbindungsprotokolle</a></span></dt></dl></dd><dt><span class="chapter"><a href="vpn-ncp-wm.php">47. VPN mit dem NCP Client f&uuml;r Windows Mobile</a></span></dt><dd><dl><dt><span class="sect1"><a href="vpn-ncp-wm.php#vpn-ncp-wm-installation">47.1. Installation</a></span></dt><dt><span class="sect1"><a href="vpn-ncp-wm-certificates.php">47.2. Zertifikate</a></span></dt><dt><span class="sect1"><a href="vpn-ncp-wm-connection.php">47.3. Verbindungen</a></span></dt><dt><span class="sect1"><a href="vpn-ncp-wm-intranator.php">47.4. Intranator</a></span></dt></dl></dd><dt><span class="chapter"><a href="vpn-ncp-symbian.php">48. VPN mit dem NCP Client f&uuml;r Symbian</a></span></dt><dd><dl><dt><span class="sect1"><a href="vpn-ncp-symbian.php#vpn-ncp-symbian-installation">48.1. Installation</a></span></dt><dt><span class="sect1"><a href="vpn-ncp-symbian-certificates.php">48.2. Zertifikate</a></span></dt><dt><span class="sect1"><a href="vpn-ncp-symbian-connection.php">48.3. Verbindungen</a></span></dt><dt><span class="sect1"><a href="vpn-ncp-symbian-intranator.php">48.4. Intranator</a></span></dt></dl></dd><dt><span class="chapter"><a href="vpn-net.php">49. Anbinden von kompletten Netzen</a></span></dt><dd><dl><dt><span class="sect1"><a href="vpn-net.php#vpn-net-concept">49.1. Konzept</a></span></dt><dt><span class="sect1"><a href="vpn-net-intranator.php">49.2. Konfiguration auf dem Intranator</a></span></dt><dd><dl><dt><span class="sect2"><a href="vpn-net-intranator.php#vpn-net-intranator-prereq">49.2.1. Voraussetzungen</a></span></dt><dt><span class="sect2"><a href="vpn-net-intranator.php#vpn-net-intranator-basicconfig">49.2.2. Grundeinstellungen</a></span></dt><dt><span class="sect2"><a href="vpn-net-intranator.php#vpn-net-intranator-auth">49.2.3. Authentifizierung</a></span></dt><dt><span class="sect2"><a href="vpn-net-intranator.php#vpn-net-intranator-tunnel">49.2.4. Tunnel konfigurieren</a></span></dt><dt><span class="sect2"><a href="vpn-net-intranator.php#vpn-net-intranator-rights">49.2.5. Rechte</a></span></dt><dt><span class="sect2"><a href="vpn-net-intranator.php#vpn-net-intranator-activation">49.2.6. Aktivierung</a></span></dt></dl></dd></dl></dd><dt><span class="chapter"><a href="vpn-zywall-router.php">50. VPN mit ZyXEL ZyWALL Routern</a></span></dt><dd><dl><dt><span class="sect1"><a href="vpn-zywall-router.php#vpn-zywall-router-overview">50.1. &Uuml;berblick</a></span></dt><dt><span class="sect1"><a href="vpn-zywall-router-prepare.php">50.2. Vorbereitung</a></span></dt><dt><span class="sect1"><a href="vpn-zywall-router-intranator-cert.php">50.3. Installieren des Intranator-Zertifikats</a></span></dt><dt><span class="sect1"><a href="vpn-zywall-router-cert.php">50.4. Erzeugen und Installieren des Router-Zertifikats</a></span></dt><dt><span class="sect1"><a href="vpn-zywall-router-vpn.php">50.5. Konfiguration der VPN-Verbindung</a></span></dt><dt><span class="sect1"><a href="vpn-zywall-router-intranator.php">50.6. Intranator</a></span></dt></dl></dd><dt><span class="chapter"><a href="vpn-zywall-usg.php">51. VPN mit ZyXEL ZyWALL USG</a></span></dt><dd><dl><dt><span class="sect1"><a href="vpn-zywall-usg.php#vpn-zywall-usg-overview">51.1. &Uuml;berblick</a></span></dt><dt><span class="sect1"><a href="vpn-zywall-usg-prepare.php">51.2. Vorbereitung</a></span></dt><dt><span class="sect1"><a href="vpn-zywall-usg-certificates.php">51.3. Zertifikate</a></span></dt><dt><span class="sect1"><a href="vpn-zywall-usg-connection.php">51.4. Verbindung</a></span></dt><dd><dl><dt><span class="sect2"><a href="vpn-zywall-usg-connection.php#vpn-zywall-usg-connection-ike">51.4.1. IKE / Phase 1</a></span></dt><dt><span class="sect2"><a href="vpn-zywall-usg-connection.php#vpn-zywall-usg-connection-ipsec">51.4.2. IPSec / Phase 2</a></span></dt></dl></dd><dt><span class="sect1"><a href="vpn-zywall-usg-intranator.php">51.5. Intranator</a></span></dt><dt><span class="sect1"><a href="vpn-zywall-usg-logs.php">51.6. Logs</a></span></dt></dl></dd><dt><span class="chapter"><a href="vpn-lancom-router.php">52. VPN mit Lancom Routern</a></span></dt><dd><dl><dt><span class="sect1"><a href="vpn-lancom-router.php#vpn-lancom-router-overview">52.1. &Uuml;berblick</a></span></dt><dt><span class="sect1"><a href="vpn-lancom-router-certificates.php">52.2. Zertifikat f&uuml;r das Lancom-Ger&auml;t</a></span></dt><dt><span class="sect1"><a href="vpn-lancom-router-certificate-intranator.php">52.3. Zertifikat f&uuml;r den Intranator</a></span></dt><dt><span class="sect1"><a href="vpn-lancom-router-connection.php">52.4. Verbindung</a></span></dt><dt><span class="sect1"><a href="vpn-lancom-router-intranator.php">52.5. Intranator</a></span></dt><dt><span class="sect1"><a href="vpn-lancom-router-delcert.php">52.6. Zertifikate l&ouml;schen</a></span></dt></dl></dd><dt><span class="chapter"><a href="vpn-linux-xswan.php">53. VPN mit Linux</a></span></dt><dd><dl><dt><span class="sect1"><a href="vpn-linux-xswan.php#vpn-linux-xswan-overview">53.1. &Uuml;berblick</a></span></dt><dt><span class="sect1"><a href="vpn-linux-xswan-cert.php">53.2. Zertifikate erzeugen</a></span></dt><dt><span class="sect1"><a href="vpn-linux-xswan-connection.php">53.3. Verbindungen konfigurieren</a></span></dt><dt><span class="sect1"><a href="vpn-linux-xswan-intranator.php">53.4. Intranator</a></span></dt></dl></dd><dt><span class="chapter"><a href="vpn-nat.php">54. L&ouml;sen von IP-Adresskonflikten in VPNs durch NAT</a></span></dt><dd><dl><dt><span class="sect1"><a href="vpn-nat.php#vpn-nat-description">54.1. Das Problem</a></span></dt><dt><span class="sect1"><a href="vpn-nat-configuration.php">54.2. Konfiguration</a></span></dt><dt><span class="sect1"><a href="vpn-nat-example-sameip-lan-remote.php">54.3. Gleiche IPs in LAN und auf der Gegenseite</a></span></dt><dd><dl><dt><span class="sect2"><a href="vpn-nat-example-sameip-lan-remote.php#vpn-nat-example-sameip-lan-remote-solution">54.3.1. Umsetzung</a></span></dt></dl></dd><dt><span class="sect1"><a href="vpn-nat-example-multiple-remote-sameip.php">54.4. Mehrere Gegenstellen mit gleichen IPs</a></span></dt><dd><dl><dt><span class="sect2"><a href="vpn-nat-example-multiple-remote-sameip.php#vpn-nat-example-multiple-remote-sameip-solution">54.4.1. Umsetzung</a></span></dt></dl></dd><dt><span class="sect1"><a href="vpn-nat-example-localip-adapt.php">54.5. Lokale IPs festgelegt durch Fernwartungs-Dienstleister</a></span></dt><dd><dl><dt><span class="sect2"><a href="vpn-nat-example-localip-adapt.php#vpn-nat-example-localip-adapt-solution">54.5.1. Umsetzung</a></span></dt></dl></dd></dl></dd><dt><span class="chapter"><a href="vpn-common-errors.php">55. Fehlerdiagnose</a></span></dt><dd><dl><dt><span class="sect1"><a href="vpn-common-errors.php#vpn-common-errors-logreading">55.1. Logs lesen</a></span></dt><dt><span class="sect1"><a href="vpn-common-errors-logformat.php">55.2. Das Protokollformat des Intranators</a></span></dt><dt><span class="sect1"><a href="vpn-common-errors-phase1.php">55.3. Fehler in Phase 1</a></span></dt><dt><span class="sect1"><a href="vpn-common-errors-phase2.php">55.4. Fehler in Phase 2</a></span></dt></dl></dd></dl></div></div><div class="navfooter"><hr><table width="100%" summary="Navigation footer"><tr><td width="40%" align="left"><a accesskey="p" href="firewall-examples-dmz.php">Zur&uuml;ck</a>&nbsp;</td><td width="20%" align="center">&nbsp;</td><td width="40%" align="right">&nbsp;<a accesskey="n" href="vpn-basics.php">Weiter</a></td></tr><tr><td width="40%" align="left" valign="top">37.5. Aufgabe 5: Webserver in der DMZ&nbsp;</td><td width="20%" align="center"><a accesskey="h" href="index.php">Zum Anfang</a></td><td width="40%" align="right" valign="top">&nbsp;38. Kapitel - IPSec Grundlagen</td></tr></table></div>
      
    <!-- content end -->
    </div>

  <!-- footer start -->

</div> <!-- close content <div> -->
</div> <!-- close page <div> -->

<div id="sitemap">

<div id="sitemapcol1">
	<a href="../../../produkte/index.php" class="sitemapheader">Produkte</a>
	<ul class="sitemap">
	<li><a href="../../../produkte/intranator.php">Intra2net Business Server</a></li>
	<li><a href="../../../produkte/security_gateway.php">Intra2net Security Gateway</a></li>
	<li><a href="../../../produkte/network_security.php">Intra2net Network Security</a></li>
	<li><a href="../../../produkte/appliance_eco.php">Intra2net Appliance Eco</a></li>
	<li><a href="../../../produkte/appliance_pro.php">Intra2net Appliance Pro</a></li>
	<li><a href="../../../produkte/appliance_ultimate.php">Intra2net Appliance Ultimate</a></li>
	</ul>
</div>

<div id="sitemapcol2">
	<a href="../../../download/index.php" class="sitemapheader">Download</a>
	<ul class="sitemap">
	<li><a href="../../../download/index.php">Software</a></li>
	<li><a href="../../../download/datenblaetter.php">Datenbl&auml;tter</a></li>
	<li><a href="../../../download/handbuecher.php">Handb&uuml;cher</a></li>
	</ul>
</div>

<div id="sitemapcol3">
	<a href="../../index.php" class="sitemapheader">Support</a>
	<ul class="sitemap">
	<li><a href="../../anfrage.php">Support-Anfrage</a></li>
	<li><a href="../../handbuecher.php">Handb&uuml;cher</a></li>
	<li><a href="http://forum.intra2net.com/">Forum</a></li>
	<li><a href="../../unterstuetzte_hardware.php">Unterst&uuml;tzte Hardware</a></li>
	<li><a href="../../antispam/index.html">Blacklist Performance</a></li>
	<li><a href="../../schulung.php">Schulung</a></li>
	<li><a href="../../fernwartung.php">Fernwartung</a></li>
	</ul>
</div>

<div id="sitemapcol4">
	<a href="../../../kaufen/index.php" class="sitemapheader">Kaufen</a>
	<ul class="sitemap">
	<li><a href="../../../kaufen/index.php">Partner finden</a></li>
	<li><a href="../../../partner-werden">Partner werden</a></li>
	<li><a href="https://partner.intra2net.com/">Partnerweb</a></li>
	</ul>
</div>

<div id="sitemapcol5">
	<a href="../../../unternehmen/index.php" class="sitemapheader">Unternehmen</a>
	<ul class="sitemap">
	<li><a href="../../../unternehmen/index.php">&Uuml;ber Intra2net</a></li>
	<li><a href="../../../unternehmen/presse/index.php">Presse</a></li>
	<li><a href="../../../unternehmen/karriere.php">Karriere</a></li>
	<li><a href="../../../unternehmen/kontakt.php">Kontakt</a></li>
	</ul>
</div>

</div> <!-- close sitemap <div> -->


<div id="footnote">
	<div id="footnotecompany">

		&copy; Intra2net AG 2015
	</div>

	<div id="footnotelinks">
		<a href="../../../impressum.php">Impressum</a>
		<a href="../../../../en/developer/index.html">Entwickler</a>
		<a href="../../../datenschutz.php">Datenschutz</a>
		<a href="../../../unternehmen/kontakt.php">Kontakt</a>
	</div>
</div>

<script type="text/javascript">

  var _gaq = _gaq || [];
  _gaq.push(['_setAccount', 'UA-151599-1']);
  _gaq.push(['_gat._anonymizeIp'])
  _gaq.push(['_trackPageview']);

  (function() {
    var ga = document.createElement('script'); ga.type = 'text/javascript'; ga.async = true;
    ga.src = ('https:' == document.location.protocol ? 'https://ssl' : 'http://www') + '.google-analytics.com/ga.js';
    var s = document.getElementsByTagName('script')[0]; s.parentNode.insertBefore(ga, s);
  })();

</script>

<!-- PHP error counter: 0 -->

<!-- footer end -->

    </body></html>