<!DOCTYPE html>
    <html><head>
      <meta http-equiv="Content-Type" content="text/html; charset=utf-8">
   <title>Installation auf VMware vSphere Hypervisor 4 (ESXi) | Administrator Handbuch
  </title>
      <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <link rel="stylesheet" type="text/css" media="screen" href="../../../screen.css">
    <link rel="stylesheet" type="text/css" media="print" href="../../../print.css">
    <meta name="generator" content="DocBook XSL Stylesheets V1.74.3"><link rel="home" href="index.php" title="Intra2net Administrator Handbuch"><link rel="up" href="install.php" title="Teil&nbsp;1.&nbsp;Installation"><link rel="prev" href="install-virtual.php" title="4. Kapitel - Installation als virtuelle Maschine"><link rel="next" href="install-virtual-vmware-directnic.php" title="5.2. Virtuelle Maschine mit direktem Internetzugang">
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

<a href="install-virtual-vmware.php#navigation"><div class="mobilemenu"><img src="../../../pictures/mobile_icon.gif" alt="Navigation"></div></a>
<a href="install-virtual-vmware.php#"><div class="mobilemenu"><img src="../../../pictures/mobile_icon.gif" alt="Navigation"></div></a>

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

    <div class="navheader"><table width="100%" summary="Navigation header"><tr><th colspan="3" align="center">5. Kapitel - Installation auf VMware vSphere Hypervisor 4 (ESXi)</th></tr><tr><td width="20%" align="left"><a accesskey="p" href="install-virtual.php">Zur&uuml;ck</a>&nbsp;</td><th width="60%" align="center">Teil&nbsp;1.&nbsp;Installation</th><td width="20%" align="right">&nbsp;<a accesskey="n" href="install-virtual-vmware-directnic.php">Weiter</a></td></tr></table><hr></div><div class="chapter" lang="de"><div class="titlepage"><div><div><h2 class="title"><a name="install-virtual-vmware"></a>5. Kapitel - Installation auf <span class="productname">VMware vSphere Hypervisor</span>&#8482; 4 (ESXi)</h2></div></div></div><div class="toc"><p><b>Inhaltsverzeichnis</b></p><dl><dt><span class="sect1"><a href="install-virtual-vmware.php#install-virtual-vmware-config">5.1. Konfiguration der virtuellen Maschine</a></span></dt><dt><span class="sect1"><a href="install-virtual-vmware-directnic.php">5.2. Virtuelle Maschine mit direktem Internetzugang</a></span></dt><dt><span class="sect1"><a href="install-virtual-vmware-install.php">5.3. Installation des Intranators</a></span></dt></dl></div><a class="indexterm" name="install-virtual-vmware-install1"></a><p>F&uuml;r die Basis-Virtualisierungsplattform <span class="productname">VMware vSphere
            Hypervisor</span>&#8482; (fr&uuml;her <span class="productname">VMware ESXi</span>&#8482;) wird unter
        dieser URL eine dauerhafte, kostenlose Lizenz angeboten: <a class="ulink" href="http://www.vmware.com/go/get-free-esxi" target="_top">http://www.vmware.com/go/get-free-esxi</a>.</p><p>F&uuml;r weitergehende Management- und &Uuml;berwachungsfunktionen ben&ouml;tigen sie kostenpflichtige
        Lizenzen. Eine &Uuml;bersicht &uuml;ber die verschiedenen Produkte finden Sie unter <a class="ulink" href="http://www.vmware.com/products/vsphere/compare.html" target="_top">Compare vSphere
            Editions</a>.</p><p>Der Intranator enth&auml;lt von Haus aus alle Treiber und Programme, die f&uuml;r den zuverl&auml;ssigen
        Betrieb auf <span class="productname">VMware vSphere Hypervisor</span>&#8482; 4 n&ouml;tig sind. Dies sind der
        paravirtualisierte Netzwerktreiber (VMXNET 3), der paravirtualisierte SCSI-Treiber (pvscsi)
        sowie die open-vm-tools. Eine zus&auml;tzliche Installation der VMware Tools oder anderer Treiber
        oder Programme ist nicht notwendig.</p><div class="sect1" lang="de"><div class="titlepage"><div><div><h2 class="title" style="clear: both"><a name="install-virtual-vmware-config"></a>5.1. Konfiguration der virtuellen Maschine</h2></div></div></div><p>Gehen Sie f&uuml;r die Installation einer virtuellen Maschine wie folgt vor:</p><div class="orderedlist"><ol type="1"><li><p>Starten Sie den vSphere Client, verbinden sich mit dem vSphere-Server und
                    legen eine neue VM an.</p></li><li><p>W&auml;hlen Sie die benutzerdefinierte Konfiguration.</p><div class="mediaobject"><img src="../images/install/vmware/vmware-config-01.png"></div></li><li><p>Benennen Sie die VM und weisen einen passenden Datenspeicher zu.</p></li><li><p>W&auml;hlen Sie eine virtuelle Maschine der Version 7</p><div class="mediaobject"><img src="../images/install/vmware/vmware-config-02.png"></div></li><li><p>W&auml;hlen Sie als Betriebssystem ein <span class="guimenuitem">Anderes 2.6x Linux
                        (32-Bit)</span>.</p><div class="mediaobject"><img src="../images/install/vmware/vmware-config-03.png"></div></li><li><p>Geben Sie f&uuml;r den Intranator eine oder mehr CPUs frei. Der Intranator erkennt
                    beim Start automatisch die Anzahl der verf&uuml;gbaren CPUs und nutzt diese. </p></li><li><p>Geben Sie f&uuml;r den Intranator gen&uuml;gend Arbeitsspeicher frei. Wir empfehlen
                    mindestens 2 GB bis 50 Benutzer, dar&uuml;ber entsprechend mehr.</p></li><li><p><a name="install-virtual-vmware-config-nic"></a>Schlie&szlig;en Sie Netzwerkkarten des Typs <span class="guimenuitem">VMXNET 3</span> an.
                    Die Anzahl h&auml;ngt vom Layout des lokalen Netzes und dem Einsatzzweck des
                    Intranators ab.</p><p>Es wird dringend davon abgeraten, direkt mit dem Internet verbundene
                    Netzwerkkarten auf diese Weise anzubinden. Beachten Sie dazu <a xmlns:d="http://docbook.org/ns/docbook" xmlns:xlink="http://www.w3.org/1999/xlink" href="install-virtual-vmware-directnic.php">Abschnitt&nbsp;5.2, &#8222;Virtuelle Maschine mit direktem Internetzugang&#8220;</a>.</p><div class="mediaobject"><img src="../images/install/vmware/vmware-config-05.png"></div></li><li><p> W&auml;hlen Sie einen SCSI-Controller vom Typ <span class="guimenuitem">VMware
                        Paravirtual</span>. </p><div class="mediaobject"><img src="../images/install/vmware/vmware-config-06.png"></div></li><li><p>Legen Sie eine neue virtuelle Festplatte an.</p><div class="mediaobject"><img src="../images/install/vmware/vmware-config-07.png"></div></li><li><p>Weisen Sie dem Intranator eine Festplatte von mindestens 40 GB zu. Wird der
                    Intranator nur zum Scannen von E-Mails und als HTTP-Proxyserver eingesetzt,
                    reichen diese 40 GB im Normalfall auch aus. Nur wenn umfangreiche Statistikdaten
                    f&uuml;r viele Benutzer l&auml;ngerfristig gespeichert werden sollen, wird mehr Speicher
                    ben&ouml;tigt.</p><p>Werden E-Mails oder Groupwaredaten dauerhaft auf dem Intranator abgelegt, wird
                    mehr Festplattenplatz ben&ouml;tigt. Als Faustformel gilt Folgendes: ( Gesamtes
                    E-Mail-Volumen aller Benutzer + Statistikdaten) * (Anzahl auf dem System
                    gespeicherter Backups&auml;tze + 2) + 20 GB. Die Anzahl auf dem System gespeicherter
                    Backups&auml;tze betr&auml;gt dabei mindestens 1, empfohlen wird 2.</p><p>Kalkulieren Sie immer etwas Reserve ein, da ein Vergr&ouml;&szlig;ern der Festplatte im
                    Betrieb derzeit nicht unterst&uuml;tzt wird.</p><p>Weisen Sie dem Intranator die gesamte Festplattenkapazit&auml;t sofort zu, da dies
                    in der Regel zu schnelleren Zugriffszeiten f&uuml;hrt.</p><div class="mediaobject"><img src="../images/install/vmware/vmware-config-08.png"></div></li><li><p>Weisen Sie die Festplatte auf Knoten SCSI(0:0) zu.</p><div class="mediaobject"><img src="../images/install/vmware/vmware-config-09.png"></div></li><li><p>Bearbeiten Sie die Einstellungen vor der Fertigstellung.</p><div class="mediaobject"><img src="../images/install/vmware/vmware-config-10.png"></div></li><li><p>&Ouml;ffnen Sie das Men&uuml; <span class="guimenu">Optionen</span> und aktivieren die
                        <span class="guimenuitem">VMI-Paravirtualisierung</span>.</p><div class="mediaobject"><img src="../images/install/vmware/vmware-config-11.png"></div></li></ol></div></div></div><div class="navfooter"><hr><table width="100%" summary="Navigation footer"><tr><td width="40%" align="left"><a accesskey="p" href="install-virtual.php">Zur&uuml;ck</a>&nbsp;</td><td width="20%" align="center"><a accesskey="u" href="install.php">Nach oben</a></td><td width="40%" align="right">&nbsp;<a accesskey="n" href="install-virtual-vmware-directnic.php">Weiter</a></td></tr><tr><td width="40%" align="left" valign="top">4. Kapitel - Installation als virtuelle Maschine&nbsp;</td><td width="20%" align="center"><a accesskey="h" href="index.php">Zum Anfang</a></td><td width="40%" align="right" valign="top">&nbsp;5.2. Virtuelle Maschine mit direktem Internetzugang</td></tr></table></div>
      
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